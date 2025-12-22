#pragma once
#include "Player.h"
#include "Explosion.h"
#include "config.h"
#include"BaseEnemy.h"

void InitEnemyGraphics();
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH]);
void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);
void DrawEnemies(float scrollX);
