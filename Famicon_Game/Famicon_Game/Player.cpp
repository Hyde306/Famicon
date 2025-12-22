#include "Player.h"
#include "config.h"
#include <cmath>
#include "Bomb.h"
#include "ObjBase.h"
#include "2D_function.h"

extern Bomb bomb;

// プレイヤー初期化
void Player::Init()
{
    mapX = 1;
    mapY = 1;

    pos.x = mapX * TILE_SIZE;
    pos.y = mapY * TILE_SIZE;
    vec = { 0, 0 };

    dir = DIR_DOWN;
    moveDir = -1;
    currentFrame = frameTimer = 0;

    ImgWidth = TILE_SIZE;
    ImgHeight = TILE_SIZE;

    isDead = false;
    isDeadFinished = false;
    justSolidified = false;

    deadFrame = 0;
    deadTimer = 0; 
    bombSolidDelay = 0;
    exitCount = 0;

    image = LoadGraph("image/Player.png"); // 384×192
}

// プレイヤー更新
void Player::Update(int map[MAP_HEIGHT][MAP_WIDTH],
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    centerX = pos.x + TILE_SIZE / 2;
    centerY = pos.y + TILE_SIZE / 2;
    mapX = (int)(centerX) / TILE_SIZE;
    mapY = (int)(centerY) / TILE_SIZE;

    if (mapX < 0) mapX = 0;
    if (mapY < 0) mapY = 0;
    if (mapX >= MAP_WIDTH)  mapX = MAP_WIDTH - 1;
    if (mapY >= MAP_HEIGHT) mapY = MAP_HEIGHT - 1;

    // 死亡判定
    if (!isDead)
    {
        if (explosions[mapY][mapX].active)
        {
            isDead = true;
            deadFrame = 0;
            deadTimer = 0;
            vec = { 0,0 };
            return;
        }
    }

    // 死亡アニメ進行
    if (isDead)
    {
        deadTimer++;
        if (deadTimer % 3 == 0 && deadFrame < DEAD_COUNT - 1)
        {
            deadFrame++;
        }

        if (deadFrame >= DEAD_COUNT - 1)
        {
            isDeadFinished = true;
        }
        return;
    }

    // 入力処理
    vec = { 0,0 };
    if (CheckHitKey(KEY_INPUT_A)) { vec.x = -MOVE_INTERVAL; dir = DIR_LEFT;  moveDir = DIR_LEFT; }
    else if (CheckHitKey(KEY_INPUT_D)) { vec.x = MOVE_INTERVAL; dir = DIR_RIGHT; moveDir = DIR_RIGHT; }
    else if (CheckHitKey(KEY_INPUT_W)) { vec.y = -MOVE_INTERVAL; dir = DIR_UP;    moveDir = DIR_UP; }
    else if (CheckHitKey(KEY_INPUT_S)) { vec.y = MOVE_INTERVAL; dir = DIR_DOWN;  moveDir = DIR_DOWN; }
    else moveDir = -1;

    // 壁の当たり判定
    const float radius = TILE_SIZE / 2.0f;

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x] == 1 || map[y][x] == 2)
            {
                BlockStub block(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
                HitCheck_Box_Circle(this, &block, radius);
            }
        }
    }

    // ボム通り抜け制御
    if (bomb.active)
    {
        float dx = centerX - (bomb.worldX + TILE_SIZE / 2);
        float dy = centerY - (bomb.worldY + TILE_SIZE / 2);

        if (bomb.passThrough)
        {
            bool outX = std::fabs(dx) >= TILE_SIZE;
            bool outY = std::fabs(dy) >= TILE_SIZE;

            if (outX || outY)
            {
                exitCount++;
                if (exitCount >= 2)  
                {
                    bomb.passThrough = false;
                }
            }
            else
            {
                exitCount = 0;
            }
        }
        else
        {
            // 通り抜け終了後は普通の障害物として扱う
            BlockStub bombBlock(bomb.worldX, bomb.worldY, TILE_SIZE);
            HitCheck_Box_Circle(this, &bombBlock, radius);
        }
    }

    // 押し戻し後の移動適用
    pos.x += vec.x;
    pos.y += vec.y;

    // アニメーション更新
    if (moveDir != -1)
    {
        frameTimer++;
        if (frameTimer >= FRAME_INTERVAL)
        {
            frameTimer = 0;
            currentFrame = (currentFrame + 1) % 3;
        }
    }
    else
    {
        currentFrame = 1;
    }

    // マップ座標を再計算
    centerX = pos.x + TILE_SIZE / 2;
    centerY = pos.y + TILE_SIZE / 2;
    mapX = (int)(centerX) / TILE_SIZE;
    mapY = (int)(centerY) / TILE_SIZE;

}

bool Player::WantsToPlaceBomb() const
{
    return CheckHitKey(KEY_INPUT_SPACE);
}

// 描画
void Player::Draw(float scrollX)
{
    if (isDeadFinished)
        return;  // 完全に表示しない

    int x = (int)(pos.x - scrollX);
    int y = (int)(pos.y);

    // 死亡アニメ
    if (isDead)
    {
        int srcX = deadFrame * FRAME_WIDTH;         // 0〜5コマ
        int srcY = 2 * FRAME_HEIGHT;                //  2行目

        DrawRectGraph(x, y, srcX, srcY,
            FRAME_WIDTH, FRAME_HEIGHT,
            image, TRUE);
        return;
    }

    int srcX = 0;
    int srcY = 0;

    if (dir == DIR_LEFT) 
    {
        srcY = 0 * FRAME_HEIGHT;
        srcX = currentFrame * FRAME_WIDTH;
    }
    else if (dir == DIR_DOWN)
    {
        srcY = 0 * FRAME_HEIGHT;
        srcX = (currentFrame + 3) * FRAME_WIDTH;
    }
    else if (dir == DIR_RIGHT) 
    {
        srcY = 1 * FRAME_HEIGHT;
        srcX = currentFrame * FRAME_WIDTH;
    }
    else if (dir == DIR_UP)
    {
        srcY = 1 * FRAME_HEIGHT;
        srcX = (currentFrame + 3) * FRAME_WIDTH;
    }

    DrawRectGraph(x, y, srcX, srcY, FRAME_WIDTH, FRAME_HEIGHT, image, TRUE);
}

void Player::Kill()
{
    if (!isDead)
    {
        isDead = true;
        deadFrame = 0;
        deadTimer = 0;
        vec = { 0,0 };
    }
}

int Player::Action(std::list<std::unique_ptr<Base>>&)
{
    return 0;
}
void Player::Draw()
{
}

float Player::GetCenterX() const { return centerX; }
float Player::GetCenterY() const { return centerY; }
int Player::GetMapX() const { return mapX; }
int Player::GetMapY() const { return mapY; }
float Player::GetWorldX() const { return pos.x; }
float Player::GetWorldY() const { return pos.y; }
