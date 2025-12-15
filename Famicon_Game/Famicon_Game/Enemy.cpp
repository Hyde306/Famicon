// Enemy.cpp
#include "Enemy.h"
#include "DxLib.h"
#include "2D_function.h"

extern Bomb bomb;

int enemyImg; // スプライトシート1枚
static std::vector<std::unique_ptr<Base>> enemies;

// 敵画像の初期化
void InitEnemyGraphics() {
    enemyImg = LoadGraph("image/Enemy1.png"); // 横に6フレーム並んでいる想定
}

// 敵生成
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH]) {
    enemies.clear();
    auto c = std::make_unique<ChaseEnemy>();
    c->Init(map);
    enemies.push_back(std::move(c));
}

// 敵更新
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH]) {
    for (auto& e : enemies) {
        auto* chase = dynamic_cast<ChaseEnemy*>(e.get());
        if (chase) chase->Update(map, player, explosions);
    }
}

// 敵描画
void DrawEnemies(float scrollX) {
    for (auto& e : enemies) {
        auto* chase = dynamic_cast<ChaseEnemy*>(e.get());
        if (chase) chase->Draw(scrollX);
    }
}

// ===== ChaseEnemy =====
void ChaseEnemy::Init(int map[MAP_HEIGHT][MAP_WIDTH]) {
    pos.x = static_cast<float>(TILE_SIZE * 5);
    pos.y = static_cast<float>(TILE_SIZE * 5);
    vec.x = static_cast<float>(TILE_SIZE) / 10.0f;
    vec.y = static_cast<float>(TILE_SIZE) / 10.0f;
}

void ChaseEnemy::Update(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH]) {
    if (!alive) return;

    // プレイヤー追跡
    if (player.pos.x > pos.x) pos.x += vec.x;
    else if (player.pos.x < pos.x) pos.x -= vec.x;
    if (player.pos.y > pos.y) pos.y += vec.y;
    else if (player.pos.y < pos.y) pos.y -= vec.y;

    // アニメーション更新
    frameTimer++;
    if (frameTimer % 10 == 0) {
        currentFrame++;
        if (currentFrame >= ENEMY_FRAMES) currentFrame = 0;
    }

    // 爆風判定
    int mapX = static_cast<int>((pos.x + TILE_SIZE / 2) / TILE_SIZE);
    int mapY = static_cast<int>((pos.y + TILE_SIZE / 2) / TILE_SIZE);
    if (explosions[mapY][mapX].active) {
        alive = false;
        deathFrame = 0;
    }
}

// Base::Draw() のオーバーライド
void ChaseEnemy::Draw() {
    if (!alive) return;

    int frameWidth = 32; // 1フレームの幅
    int frameHeight = 32; // 1フレームの高さ
    int srcX = currentFrame * frameWidth;
    int srcY = 0;

    DrawRectGraph((int)pos.x, (int)pos.y,
        srcX, srcY, frameWidth, frameHeight,
        enemyImg, TRUE);
}

void ChaseEnemy::Draw(float scrollX) {
    if (!alive) return;

    int frameWidth = 32;
    int frameHeight = 32;
    int srcX = currentFrame * frameWidth;
    int srcY = 0;

    DrawRectGraph((int)(pos.x - scrollX), (int)pos.y,
        srcX, srcY, frameWidth, frameHeight,
        enemyImg, TRUE);
}

int ChaseEnemy::Action(std::list<std::unique_ptr<Base>>&) {
    return 0;
}
