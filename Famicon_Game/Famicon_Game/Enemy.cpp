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

// 敵画像の初期化
void InitEnemyGraphics() {
    enemyImg = LoadGraph("image/Enemy1.png");
}

// 敵生成
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH]) {
    enemies.clear();
    auto e = std::make_unique<ChaseEnemy>();
    e->Init(map);
    enemies.push_back(std::move(e));
}

// 敵更新
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH]) {

    for (auto& e : enemies) {
        auto* enemy = dynamic_cast<ChaseEnemy*>(e.get());
        if (enemy) enemy->Update(map, player, explosions);
    }
}

// 敵描画
void DrawEnemies(float scrollX) {
    for (auto& e : enemies) {
        auto* enemy = dynamic_cast<ChaseEnemy*>(e.get());
        if (enemy) enemy->Draw(scrollX);
    }
}

// ===== ChaseEnemy =====

void ChaseEnemy::Init(int map[MAP_HEIGHT][MAP_WIDTH]) {
    pos.x = TILE_SIZE * 5.0f;
    pos.y = TILE_SIZE * 5.0f;
    vec.y = TILE_SIZE / 10.0f;
    dirY = 1;          // 下方向
    alive = true;
    currentFrame = 0;
    frameTimer = 0;
    prevCenterY = pos.y + TILE_SIZE / 2.0f;
    alive = true;
    dying = false;
    deathFrame = 0;
    deathTimer = 0;

}

void ChaseEnemy::Update(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player&,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    if (!alive) return;

    // 中心座標
    float centerX = pos.x + TILE_SIZE / 2.0f;
    float centerY = pos.y + TILE_SIZE / 2.0f;
    int mapX = (int)(centerX / TILE_SIZE);
    int mapY = (int)(centerY / TILE_SIZE);

    // 壁判定による上下反転
    float tileCenterY = mapY * TILE_SIZE + TILE_SIZE / 2.0f;
    if ((prevCenterY - tileCenterY) * (centerY - tileCenterY) <= 0.0f)
    {
        int nextMapY = mapY + dirY;

        // 次のタイルが壁か爆弾なら反転
        bool isWall =
            (nextMapY < 0 || nextMapY >= MAP_HEIGHT ||
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

    // 移動量
    float nextY = pos.y + vec.y * dirY;
    pos.y = nextY;



    if (explosions[mapY][mapX].active)
    {
        alive = false;
        dying = true;
        deathFrame = 0;
        deathTimer = 0;
        return;
    }


    // アニメーション更新
    frameTimer++;
    if (frameTimer % 10 == 0)
    {
        currentFrame++;
        if (currentFrame >= ENEMY_FRAMES) currentFrame = 0;
    }
}


// 描画
void ChaseEnemy::Draw(float scrollX) {
    if (!alive) return;

    int frameWidth = 64;
    int frameHeight = 64;

    DrawRectGraph(
        (int)(pos.x - scrollX),
        (int)pos.y,
        currentFrame * frameWidth,
        0,
        frameWidth,
        frameHeight,
        enemyImg,
        TRUE
    );
}

int ChaseEnemy::Action(std::list<std::unique_ptr<Base>>&) {
    return 0;
}

void ChaseEnemy::Draw() {
    Draw(0.0f);
}
