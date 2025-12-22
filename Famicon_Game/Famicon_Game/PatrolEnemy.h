#pragma once
#include "BaseEnemy.h"
#include "Player.h"
#include "Explosion.h"
#include "config.h"

class PatrolEnemy : public BaseEnemy
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

    void Init(int map[MAP_HEIGHT][MAP_WIDTH]) override;
    void Update(int map[MAP_HEIGHT][MAP_WIDTH],
        Player& player,
        Explosion explosions[MAP_HEIGHT][MAP_WIDTH]) override;
    void Draw() override;
    void Draw(float scrollX);

    int Action(std::list<std::unique_ptr<Base>>&) override;
    bool IsDead() const override;

private:
    int dirX = 1;
    float prevCenterX = 0.0f;
    static const int DEAD_COUNT = 5;
};
