#include "ChaseEnemy.h"
#include "DxLib.h"
#include "Bomb.h"

extern Bomb bomb;
extern int enemyImg;

void ChaseEnemy::Init(int map[MAP_HEIGHT][MAP_WIDTH])
{
    pos.x = TILE_SIZE * 5.0f;
    pos.y = TILE_SIZE * 5.0f;

    vec.y = TILE_SIZE / 10.0f;  // Å© èCê≥É|ÉCÉìÉg
    dirY = 1;

    alive = true;
    dying = false;
    isDeadFinished = false;

    currentFrame = 0;
    frameTimer = 0;

    deathFrame = 0;
    deathTimer = 0;

    prevCenterY = pos.y + TILE_SIZE / 2.0f;
}

void ChaseEnemy::Update(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
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

    float tileCenterY = mapY * TILE_SIZE + TILE_SIZE / 2.0f;

    if ((prevCenterY - tileCenterY) * (centerY - tileCenterY) <= 0.0f)
    {
        int nextMapY = mapY + dirY;

        bool isWall =
            (nextMapY < 0 ||
                nextMapY >= MAP_HEIGHT ||
                map[nextMapY][mapX] == 1 ||
                map[nextMapY][mapX] == 2);

        bool isBomb = false;
        if (bomb.active)
        {
            if (bomb.mapX == mapX && bomb.mapY == nextMapY)
                isBomb = true;
        }

        if (isWall || isBomb)
            dirY = -dirY;

        pos.y = tileCenterY - TILE_SIZE / 2.0f;
    }

    prevCenterY = centerY;

    pos.y += vec.y * dirY;

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
}

void ChaseEnemy::Draw(float scrollX)
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
bool ChaseEnemy::IsDead() const
{
    return isDeadFinished;
}
void ChaseEnemy::Draw()
{
    Draw(0.0f);
}
int ChaseEnemy::Action(std::list<std::unique_ptr<Base>>&)
{
    return 0;
}
