//Map.cpp
#include "Map.h"
#include"DxLib.h"

int map[MAP_HEIGHT][MAP_WIDTH] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,2,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,2,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,2,0,2,0,0,2,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,2,1,2,1,0,1,0,1,0,1,0,1,0,1,2,1,2,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,2,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,2,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,2,1,0,1,0,1,2,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,2,0,0,0,0,2,2,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// 画像
static int wallImage;
static int floorImage;
static int softBlockImage;

// 画像読み込み
void InitMapGraphics() {
    floorImage = LoadGraph("image/Ground.png");
    wallImage = LoadGraph("image/Block.png");
    softBlockImage = LoadGraph("image/Break.png");
}

// マップ描画
void DrawMap(float scrollX)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            int drawX = x * TILE_SIZE - (int)scrollX;
            int drawY = y * TILE_SIZE;

            // 画面外なら描画しない
            if (drawX + TILE_SIZE < 0 || drawX > WINDOW_WIDTH) continue;

            // マップの値に応じて描画
            if (map[y][x] == 0) 
            {
                DrawGraph(drawX, drawY, floorImage, TRUE);
            }
            else if (map[y][x] == 1) 
            {
                DrawGraph(drawX, drawY, wallImage, TRUE);
            }
            else if (map[y][x] == 2) 
            {
                DrawGraph(drawX, drawY, softBlockImage, TRUE);
            }
        }
    }
}
