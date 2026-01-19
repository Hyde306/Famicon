#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Explosion.h"
#include "config.h"

class ONeillEnemy : public BaseEnemy
{
public:
    Position pos;
    Vec2 vec;
    bool dying = false;
    bool isDeadFinished = false;
    int currentFrame = 0;
    int deathFrame = 0;
    int deathTimer = 0;

    void Init(int map[MAP_HEIGHT][MAP_WIDTH]) override;
    void Update(int map[MAP_HEIGHT][MAP_WIDTH], Player& player, Explosion explosions[MAP_HEIGHT][MAP_WIDTH]) override;
    void Draw() override;
    void Draw(float scrollX);

    bool IsDead() const override;
    int Action(std::list<std::unique_ptr<Base>>&) override { return 0; }

private:
    int dirX = 0;
    int dirY = 0;

    int thinkTimer = 0; // Åö A* ÇégÇ§ä‘äu
};
