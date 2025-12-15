#pragma once
#include "ObjBase.h"
#include "Player.h"
#include "Explosion.h"
#include "Bomb.h"
#include "config.h"

#define ENEMY_FRAMES 6
#define ENEMY_DEATH_FRAMES 4

extern int enemyImgs[ENEMY_FRAMES + ENEMY_DEATH_FRAMES];
extern const float MOVE_SPEED;

class ChaseEnemy : public Base {
public:
    Position pos;
    Vec2 vec;
    bool alive = true;
    int currentFrame = 0;
    int deathFrame = 0;
    int frameTimer;
    void Init(int map[MAP_HEIGHT][MAP_WIDTH]);
    void Update(int map[MAP_HEIGHT][MAP_WIDTH],
        const Player& player,
        Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);

    // Base::Draw() をオーバーライド
    void Draw() override;            // ← 引数なし版
    void Draw(float scrollX);        // ← スクロール対応版（独自）

    int Action(std::list<std::unique_ptr<Base>>&) override;
};


// 管理系
void InitEnemyGraphics();
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH]);
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);
void DrawEnemies(float scrollX);
