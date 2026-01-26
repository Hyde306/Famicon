#include "ONeillEnemy.h"
#include "DxLib.h"
#include "Bomb.h"
#include "astar.h"

extern Bomb bomb;
extern int enemyImg2;
extern int globalEnemyFrame;

void ONeillEnemy::Init(int map[MAP_HEIGHT][MAP_WIDTH])
{
    pos.x = TILE_SIZE * 10;
    pos.y = TILE_SIZE * 5;

    vec.x = TILE_SIZE / 12.0f;
    vec.y = TILE_SIZE / 12.0f;

    dying = false;
    isDeadFinished = false;

    dirX = 1;
    dirY = 0;

    thinkTimer = 0;
}

void ONeillEnemy::Update(int map[MAP_HEIGHT][MAP_WIDTH], Player& player, Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    if (isDeadFinished) return;

    if (dying)
    {
        deathTimer++;
        if (deathTimer % 3 == 0 && deathFrame < 4)
            deathFrame++;

        if (deathFrame >= 4)
            isDeadFinished = true;

        return;
    }

    float centerX = pos.x + TILE_SIZE / 2;
    float centerY = pos.y + TILE_SIZE / 2;

    int ex = (int)(centerX / TILE_SIZE);
    int ey = (int)(centerY / TILE_SIZE);

    int px = player.GetMapX();
    int py = player.GetMapY();

    // タイル境目かどうか
    int tx = (int)pos.x % TILE_SIZE;
    int ty = (int)pos.y % TILE_SIZE;
    bool isCenter = (tx == 0 && ty == 0);

    //  タイル中心にいるときだけ A* 実行
    thinkTimer++;
    if (thinkTimer >= 60 && isCenter)
    {
        thinkTimer = 0;

        //  A* 用マップを作成
        int astarMap[MAP_HEIGHT][MAP_WIDTH];
        memcpy(astarMap, map, sizeof(astarMap));

        if (bomb.active)
        {
            astarMap[bomb.mapY][bomb.mapX] = 1;
        }

        //  A* に astarMap を渡す
        list<Cell> route = ROUTE_CALCULATION(MAP_WIDTH,MAP_HEIGHT,Cell(ex, ey),Cell(px, py),&astarMap[0][0]);

        if (route.size() >= 2)
        {
            auto it = route.begin();
            it++;

            Cell next = *it;

            int oldDirX = dirX;
            int oldDirY = dirY;

            dirX = (next.X > ex) ? 1 : (next.X < ex ? -1 : 0);
            dirY = (next.Y > ey) ? 1 : (next.Y < ey ? -1 : 0);

            if (dirX == 0 && dirY == 0)
            {
                dirX = oldDirX;
                dirY = oldDirY;
            }
        }
    }

    int nextX = ex + dirX;
    int nextY = ey + dirY;

    bool blocked = nextX < 0 || nextX >= MAP_WIDTH || nextY < 0 || nextY >= MAP_HEIGHT || 
        map[nextY][nextX] == 1 ||map[nextY][nextX] == 2 || 
        (bomb.active && bomb.mapX == nextX && bomb.mapY == nextY);

    if (!blocked)
    {
        pos.x += vec.x * dirX;
        pos.y += vec.y * dirY;
    }
    else
    {
        thinkTimer = 60;  // 次フレームで必ずA*が走る

        // タイル中心にスナップ
        pos.x = ex * TILE_SIZE;
        pos.y = ey * TILE_SIZE;
    }

    // 爆風で死亡
    if (explosions[ey][ex].active)
    {
        dying = true;
        deathFrame = 0;
        deathTimer = 0;
        return;
    }

    // プレイヤー接触
    if (fabs(player.GetCenterX() - centerX) < TILE_SIZE * 0.5f &&
        fabs(player.GetCenterY() - centerY) < TILE_SIZE * 0.5f)
    {
        player.Kill();
        return;
    }

    currentFrame = globalEnemyFrame;
}

void ONeillEnemy::Draw(float scrollX)
{
    if (isDeadFinished) return;

    int x = (int)(pos.x - scrollX);
    int y = (int)(pos.y);

    int frameWidth = 64;

    int srcX = dying ? (NORMAL_FRAME_COUNT + deathFrame) * frameWidth : currentFrame * frameWidth;

    DrawRectGraph(x, y, srcX, 0, frameWidth, 64, enemyImg2, TRUE);
}

void ONeillEnemy::Draw()
{
    Draw(0.0f);
}
bool ONeillEnemy::IsDead() const
{
    return isDeadFinished;
}
