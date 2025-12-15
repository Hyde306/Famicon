#pragma once
#include "DxLib.h"
#include "config.h"
#include "BreakEffect.h"

struct Explosion
{
    bool active = false;
    int timer = 0;
    int direction = 0; // 0=center, 1=up, 2=down, 3=left, 4=right
    int currentFrame = 0;
    int frameTimer = 0;
};

extern int imgSmallCenter;
extern int imgBigCenter;
extern int imgSmallStick;
extern int imgBigStick;
extern int bombImg;
extern int breakImg;
extern int breakeffect;
extern Explosion explosions[MAP_HEIGHT][MAP_WIDTH];

// ä÷êîêÈåæ
void CreateExplosion(
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
    int map[MAP_HEIGHT][MAP_WIDTH],
    BreakEffect breakEffects[16],
    int bombX,
    int bombY,
    int power
);

void UpdateExplosion(Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);
void DrawExplosion(
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
    float scrollX,
    int imgSmallCenter,
    int imgBigCenter,
    int imgSmallStick,
    int imgBigStick
);

void InitExplosions(Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);
