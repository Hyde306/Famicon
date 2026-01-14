// Enemy.h
#pragma once
#include "ObjBase.h"
#include "Player.h"
#include "Explosion.h"
#include "config.h"

constexpr int NORMAL_FRAME_COUNT = 6;
constexpr int DEAD_FRAME_COUNT = 5;

class BaseEnemy : public Base
{
public:
    virtual void Init(int map[MAP_HEIGHT][MAP_WIDTH]) = 0;
    virtual void Update(int map[MAP_HEIGHT][MAP_WIDTH],Player& player,Explosion explosions[MAP_HEIGHT][MAP_WIDTH]) = 0;
    virtual void Draw(float scrollX) = 0;
    virtual bool IsDead() const = 0;

    void Draw() override { Draw(0.0f); }
};

void InitEnemyGraphics();
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH]);
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],Player& player,Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);
void DrawEnemies(float scrollX);
