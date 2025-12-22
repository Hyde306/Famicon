#pragma once
#include "ObjBase.h"
#include "Player.h"
#include "Explosion.h"
#include "Bomb.h"
#include "config.h"

constexpr int NORMAL_FRAME_COUNT = 6;
constexpr int DEAD_FRAME_COUNT = 5;

extern int enemyImg;

class ChaseEnemy : public Base
{
public:
    Position pos;
    Vec2 vec;
    bool alive = true;
    int currentFrame = 0;
    int frameTimer = 0;
    bool dying;        // 死亡アニメ中か
    int  deathFrame;   // 死亡アニメのコマ
    int  deathTimer;   // フレーム管理
    bool isDeadFinished;// 死亡後削除

    void Init(int map[MAP_HEIGHT][MAP_WIDTH]);
    void Update(int map[MAP_HEIGHT][MAP_WIDTH],
        const Player& player,
        Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);

    void Draw() override;
    void Draw(float scrollX);

    int Action(std::list<std::unique_ptr<Base>>&) override;

private:
    int dirY;
    float prevCenterY;
    static const int DEAD_COUNT = 5;  
};

// 管理系
void InitEnemyGraphics();
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH]);
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);
void DrawEnemies(float scrollX);
