#pragma once
#include "ObjBase.h"
#include "Player.h"
#include "Explosion.h"
#include "Bomb.h"
#include "config.h"

#define ENEMY_FRAMES 6
#define ENEMY_DEATH_FRAMES 4

extern int enemyImg;

class ChaseEnemy : public Base {
public:
    Position pos;
    Vec2 vec;
    bool alive = true;
    int currentFrame = 0;
    int deathFrame = 0;
    int frameTimer = 0;

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
};

// ä«óùån
void InitEnemyGraphics();
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH]);
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);
void DrawEnemies(float scrollX);
