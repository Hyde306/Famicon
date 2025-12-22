#pragma once
#include "ObjBase.h"
#include "Player.h"
#include "Explosion.h"
#include "Bomb.h"
#include "config.h"
#include"BaseEnemy.h"

constexpr int NORMAL_FRAME_COUNT = 6;
constexpr int DEAD_FRAME_COUNT = 5;

extern int enemyImg;

class ChaseEnemy : public BaseEnemy
{
public:
    Position pos;
    Vec2 vec;
    bool alive = true;
    int currentFrame = 0;
    int frameTimer = 0;
    bool dying = false;
    int  deathFrame = 0;
    int  deathTimer = 0;
    bool isDeadFinished = false;
    bool IsDead() const override;

    void Init(int map[MAP_HEIGHT][MAP_WIDTH]);
    void Update(int map[MAP_HEIGHT][MAP_WIDTH],
        const Player& player,
        Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);

    void Draw() override;
    void Draw(float scrollX);

    int Action(std::list<std::unique_ptr<Base>>&) override;

private:
    int dirY = 1;
    float prevCenterY = 0.0f;
    static const int DEAD_COUNT = 5;
};
