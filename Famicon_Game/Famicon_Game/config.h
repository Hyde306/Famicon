#pragma once

constexpr int TILE_SIZE = 64;
constexpr int MAP_WIDTH = 31;  // マップの横幅
constexpr int MAP_HEIGHT = 13;

constexpr int WINDOW_WIDTH = TILE_SIZE * 20; // ウィンドウ
constexpr int WINDOW_HEIGHT = TILE_SIZE * MAP_HEIGHT; // 896px

// プレイヤー情報
constexpr int FRAME_WIDTH = 64;
constexpr int FRAME_HEIGHT = 64;
constexpr int FRAME_INTERVAL = 2;// プレイヤーアニメーションスピード
constexpr int MOVE_INTERVAL = 8; // プレイヤースピード