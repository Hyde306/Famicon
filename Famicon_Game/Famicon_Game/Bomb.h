// Bomb.h
#pragma once
#include "config.h"
#include "Explosion.h"   

class Bomb
{
public:
   
    int mapX = 0;
    int mapY = 0;
    int worldX = 0;
    int worldY = 0;
    int timer = 0;
    int currentFrame = 0;
    int frameTimer = 0;
    bool active = false;
    bool passThrough = false;

    // ボム更新
    void Update
    (
        Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
        int map[MAP_HEIGHT][MAP_WIDTH],
        BreakEffect breakEffects[16]  
    );

    void Explode
    (
        Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
        int map[MAP_HEIGHT][MAP_WIDTH],
        BreakEffect breakEffects[16]
     );

    void UpdateAnimation();
    // ボム設置
    void Place(int mx, int my);
};
