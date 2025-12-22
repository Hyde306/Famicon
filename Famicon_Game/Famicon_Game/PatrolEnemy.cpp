#include "PatrolEnemy.h"
#include "DxLib.h"
#include "Bomb.h"

extern Bomb bomb;
extern int enemyImg;

void PatrolEnemy::Init(int map[MAP_HEIGHT][MAP_WIDTH])
{
    pos.x = TILE_SIZE * 5.0f;
    pos.y = TILE_SIZE * 7.0f;

    vec.x = TILE_SIZE / 10.0f;
    dirX = 1;

    alive = true;
    dying = false;
    isDeadFinished = false;

    currentFrame = 0;
    frameTimer = 0;

    deathFrame = 0;
    deathTimer = 0;

    prevCenterX = pos.x + TILE_SIZE / 2.0f;
}

void PatrolEnemy::Update(int map[MAP_HEIGHT][MAP_WIDTH],
    Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    if (isDeadFinished) return;

    if (dying)
    {
        deathTimer++;
        if (deathTimer % 3 == 0 && deathFrame < DEAD_COUNT - 1)
            deathFrame++;

        if (deathFrame >= DEAD_COUNT - 1)
            isDeadFinished = true;

        return;
    }

    float centerX = pos.x + TILE_SIZE / 2.0f;
    float centerY = pos.y + TILE_SIZE / 2.0f;

    int mapX = (int)(centerX / TILE_SIZE);
    int mapY = (int)(centerY / TILE_SIZE);

    float tileCenterX = mapX * TILE_SIZE + TILE_SIZE / 2.0f;

    if ((prevCenterX - tileCenterX) * (centerX - tileCenterX) <= 0.0f)
    {
        int nextMapX = mapX + dirX;

        bool isWall =
            (nextMapX < 0 ||
                nextMapX >= MAP_WIDTH ||
                map[mapY][nextMapX] == 1 ||
                map[mapY][nextMapX] == 2);

        bool isBomb = false;
        if (bomb.active)
        {
            if (bomb.mapX == nextMapX && bomb.mapY == mapY)
                isBomb = true;
        }

        if (isWall || isBomb)
            dirX = -dirX;

        pos.x = tileCenterX - TILE_SIZE / 2.0f;
    }

    prevCenterX = centerX;

    pos.x += vec.x * dirX;

    if (explosions[mapY][mapX].active)
    {
        dying = true;
        deathFrame = 0;
        deathTimer = 0;
        return;
    }

    frameTimer++;
    if (frameTimer % 10 == 0)
    {
        currentFrame++;
        if (currentFrame >= NORMAL_FRAME_COUNT)
            currentFrame = 0;
    }
    // プレイヤーとの接触判定
    {
        float px = player.GetCenterX();
        float py = player.GetCenterY();
        float ex = pos.x + TILE_SIZE / 2.0f;
        float ey = pos.y + TILE_SIZE / 2.0f;

        // 簡易AABB判定（Bomberman系ならこれで十分）
        if (fabs(px - ex) < TILE_SIZE * 0.5f &&
            fabs(py - ey) < TILE_SIZE * 0.5f)
        {
            // プレイヤー死亡
            player.Kill();

            return;
        }
    }


}

void PatrolEnemy::Draw(float scrollX)
{
    if (isDeadFinished) return;

    int x = (int)(pos.x - scrollX);
    int y = (int)(pos.y);

    const int frameWidth = 64;
    const int frameHeight = 64;

    int srcX = 0;
    int srcY = 0;

    if (dying)
        srcX = (NORMAL_FRAME_COUNT + deathFrame) * frameWidth;
    else
        srcX = currentFrame * frameWidth;

    DrawRectGraph(
        x, y,
        srcX, srcY,
        frameWidth, frameHeight,
        enemyImg,
        TRUE
    );
}

void PatrolEnemy::Draw()
{
    Draw(0.0f);
}

int PatrolEnemy::Action(std::list<std::unique_ptr<Base>>&)
{
    return 0;
}

bool PatrolEnemy::IsDead() const
{
    return isDeadFinished;
}
