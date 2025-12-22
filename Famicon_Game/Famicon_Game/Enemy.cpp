#include "Enemy.h"
#include "DxLib.h"
#include "2D_function.h"
#include <cmath>
#include <vector>
#include <memory>
#include <list>

extern Bomb bomb;

int enemyImg;
static std::vector<std::unique_ptr<Base>> enemies;

//==============================
// 敵画像初期化
//==============================
void InitEnemyGraphics()
{
    enemyImg = LoadGraph("image/Enemy1.png");
}

//==============================
// 敵生成
//==============================
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH])
{
    enemies.clear();
    auto e = std::make_unique<ChaseEnemy>();
    e->Init(map);
    enemies.push_back(std::move(e));
}

//==============================
// 敵更新
//==============================
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    for (auto& e : enemies)
    {
        auto* enemy = dynamic_cast<ChaseEnemy*>(e.get());
        if (enemy) enemy->Update(map, player, explosions);
    }
}

//==============================
// 敵描画
//==============================
void DrawEnemies(float scrollX)
{
    for (auto& e : enemies)
    {
        auto* enemy = dynamic_cast<ChaseEnemy*>(e.get());
        if (enemy) enemy->Draw(scrollX);
    }
}

//==============================
// ChaseEnemy 初期化
//==============================
void ChaseEnemy::Init(int map[MAP_HEIGHT][MAP_WIDTH])
{
    pos.x = TILE_SIZE * 5.0f;
    pos.y = TILE_SIZE * 5.0f;

    vec.y = TILE_SIZE / 10.0f;
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

//==============================
// ChaseEnemy 更新
//==============================
void ChaseEnemy::Update(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player&,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    // 完全に死亡後
    if (isDeadFinished) return;

    //------------------
    // 死亡アニメ中
    //------------------
    if (dying)
    {
        deathTimer++;
        if (deathTimer % 3 == 0 && deathFrame < DEAD_COUNT - 1)
        {
            deathFrame++;
        }

        if (deathFrame >= DEAD_COUNT - 1)
        {
            isDeadFinished = true;
        }
        return;
    }

    //------------------
    // 生存時処理
    //------------------
    float centerX = pos.x + TILE_SIZE / 2.0f;
    float centerY = pos.y + TILE_SIZE / 2.0f;

    int mapX = (int)(centerX / TILE_SIZE);
    int mapY = (int)(centerY / TILE_SIZE);

    float tileCenterY = mapY * TILE_SIZE + TILE_SIZE / 2.0f;

    // 壁・ボム判定で反転
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
            {
                isBomb = true;
            }
        }

        if (isWall || isBomb)
        {
            dirY = -dirY;
        }

        pos.y = tileCenterY - TILE_SIZE / 2.0f;
    }

    prevCenterY = centerY;

    // 移動
    pos.y += vec.y * dirY;

    // 爆風で死亡開始
    if (explosions[mapY][mapX].active)
    {
        dying = true;
        deathFrame = 0;
        deathTimer = 0;
        return;
    }

    // 通常アニメ
    frameTimer++;
    if (frameTimer % 10 == 0)
    {
        currentFrame++;
        if (currentFrame >= NORMAL_FRAME_COUNT) currentFrame = 0;
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
    int srcY = 0; // ← 常に0（1段スプライト）

    if (dying)
    {
        // 後ろ5枚を使用
        srcX = (NORMAL_FRAME_COUNT + deathFrame) * frameWidth;
    }
    else
    {
        srcX = currentFrame * frameWidth;
    }

    DrawRectGraph(
        x,
        y,
        srcX,
        srcY,
        frameWidth,
        frameHeight,
        enemyImg,
        TRUE
    );
}

//==============================
int ChaseEnemy::Action(std::list<std::unique_ptr<Base>>&)
{
    return 0;
}

void ChaseEnemy::Draw()
{
    Draw(0.0f);
}
