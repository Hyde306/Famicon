// Player.h
#pragma once
#include "DxLib.h"
#include "config.h"
#include "ObjBase.h"
#include <list>
#include "Explosion.h"

enum Direction
{
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
};

class Player : public Base
{
public:
    void Init();
    void Update(int map[MAP_HEIGHT][MAP_WIDTH],
        Explosion explosions[MAP_HEIGHT][MAP_WIDTH]);

    int Action(std::list<std::unique_ptr<Base>>&) override;
    void Draw() override; 

    int GetMapX() const;
    int GetMapY() const;
    float GetWorldX() const;
    float GetWorldY() const;
    void Draw(float scrollX);
    float GetCenterX() const;
    float GetCenterY() const;
    bool WantsToPlaceBomb() const;
    void Kill();

private:
    int mapX, mapY;
    int currentFrame;
    int frameTimer;
    int dir;
    int moveDir;
    int image;
    int bombSolidDelay = 12;   // 0ならまだ固体扱いしない
    int deadFrame;      // 死亡アニメ用フレーム
    int deadTimer;      // 死亡アニメ進行用
    int exitCount;      // ボムから外に出たフレーム
    float centerX, centerY;

    bool isDead;        // 死亡したか
    bool isDeadFinished;// 死亡後削除
    bool justSolidified;
    // 死亡アニメ行とコマ数
    static const int DEAD_ROW = 2;  // 2行目が死亡
    static const int DEAD_COUNT = 6;  // 6コマ
};
