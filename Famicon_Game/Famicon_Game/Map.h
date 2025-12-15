#pragma once
#include "config.h"
#include "DxLib.h"

// マップデータ (0:床, 1:壁, 2:壊せるブロック)
extern int map[MAP_HEIGHT][MAP_WIDTH];
// 画像読み込み
void InitMapGraphics();
// マップ描画関数
void DrawMap(float scrollX);