#include "Bomb.h"

// 初期化
void InitBomb(Bomb& bomb)
{
    bomb.active = false;
    bomb.timer = 0;
    bomb.passThrough = false; // プレイヤーのすり抜け可能か
}

//  ボムのフレーム更新
void Bomb::UpdateAnimation()
{
    frameTimer++;

    // アニメーション切り替え速度
    const int frameChange = 8;

    if (frameTimer >= frameChange)
    {
        frameTimer = 0;
        currentFrame = (currentFrame + 1) % 3;
    }
}

//  ボムの爆発処理
void Bomb::Explode
(
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
    int map[MAP_HEIGHT][MAP_WIDTH],
    BreakEffect breakEffects[16]
)
{
    active = false;

    // 爆発生成
    CreateExplosion(explosions, map, breakEffects, mapX, mapY, 2);
}

//  ボムのメイン更新
void Bomb::Update
(
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
    int map[MAP_HEIGHT][MAP_WIDTH],
    BreakEffect breakEffects[16]
)
{
    if (!active) return;

    timer--;
    UpdateAnimation(); 

    if (timer <= 0)
    {
        Explode(explosions, map, breakEffects);
    }
}

//  ボム設置
void Bomb::Place(int mx, int my)
{
    active = true;

    mapX = mx;
    mapY = my;
    worldX = mx * TILE_SIZE;
    worldY = my * TILE_SIZE;

    timer = 50;           // 爆発までの時間
    currentFrame = 0;     // アニメーション初期化
    frameTimer = 0;
    passThrough = true;   // 設置直後はすり抜け可能
}
