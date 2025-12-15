
#include "Explosion.h"
#include "config.h"
#include "DxLib.h"
#include "BreakEffect.h"

Explosion explosions[MAP_HEIGHT][MAP_WIDTH];

// 爆発配列の初期化
void InitExplosions(Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            explosions[y][x].active = false;
            explosions[y][x].timer = 0;
        }
    }
}

// 爆発を生成
void CreateExplosion(
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
    int map[MAP_HEIGHT][MAP_WIDTH],
    BreakEffect breakEffects[16],
    int bombX, int bombY, int power)
{
    const int dx[4] = { 0, 0, -1, 1 };
    const int dy[4] = { -1, 1, 0, 0 };

    explosions[bombY][bombX].active = true;
    explosions[bombY][bombX].direction = 0; // 中心
    explosions[bombY][bombX].timer = 15;

    map[bombY][bombX] = 0;

    // 各方向へ爆風を伸ばす
    for (int dir = 0; dir < 4; dir++)
    {
        for (int len = 1; len <= power; len++)
        {
            int nx = bombX + dx[dir] * len;
            int ny = bombY + dy[dir] * len;

            if (nx < 0 || ny < 0 || nx >= MAP_WIDTH || ny >= MAP_HEIGHT)
                break;

            if (map[ny][nx] == 1) break; // 固定壁

            explosions[ny][nx].active = true;
            explosions[ny][nx].direction = dir + 1;
            explosions[ny][nx].timer = 15;

            if (map[ny][nx] == 2)
            {
                map[ny][nx] = 0;

                // 壊れエフェクト生成
                for (int i = 0; i < 16; i++)
                {
                    if (!breakEffects[i].active)
                    {
                        breakEffects[i].active = true;
                        breakEffects[i].x = nx * TILE_SIZE;
                        breakEffects[i].y = ny * TILE_SIZE;
                        breakEffects[i].currentFrame = 0;
                        breakEffects[i].frameTimer = 0;
                        breakEffects[i].timer = 5;
                        break;
                    }
                }
                break;
            }
        }
    }
}

// アニメーション更新
void UpdateExplosion(Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (!explosions[y][x].active) continue;

            explosions[y][x].timer--;

            // アニメーション更新（速度調整）
            if (++explosions[y][x].frameTimer >= 3)
            {
                explosions[y][x].frameTimer = 0;
                explosions[y][x].currentFrame++;
            }

            if (explosions[y][x].timer <= 0)
                explosions[y][x].active = false;
        }
    }
}

// 爆発描画
void DrawExplosion(
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH],
    float scrollX,
    int imgSmallCenter,
    int imgBigCenter,
    int imgSmallStick,
    int imgBigStick)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (!explosions[y][x].active) continue;

            float drawX = x * TILE_SIZE - scrollX;
            float drawY = y * TILE_SIZE;
            int dir = explosions[y][x].direction;

            int maxTimer;
            if (dir == 0)
            {
                maxTimer = 10;
            }
            else 
            {
                maxTimer = 20;
            }

            bool big = (explosions[y][x].timer > maxTimer / 2);

            int imgCenter;
            int imgStick;
            if (big) 
            {
                imgCenter = imgBigCenter;
                imgStick = imgBigStick;
            }
            else 
            {
                imgCenter = imgSmallCenter;
                imgStick = imgSmallStick;
            }

            if (dir == 0)
            {
                DrawExtendGraph(
                    (int)drawX,
                    (int)drawY,
                    (int)(drawX + TILE_SIZE),
                    (int)(drawY + TILE_SIZE),
                    imgCenter,
                    TRUE
                );
            }
            else
            {
                float angle = 0.0f;
                if (dir == 1)
                {
                    angle = 0.0f;
                }
                else if (dir == 2) 
                {
                    angle = DX_PI;
                }
                else if (dir == 3)
                {
                    angle = -DX_PI / 2.0f;
                }
                else if (dir == 4) 
                {
                    angle = DX_PI / 2.0f;
                }

                int imgW, imgH;
                GetGraphSize(imgStick, &imgW, &imgH);
                float scaleX = (float)TILE_SIZE / imgW;
                float scaleY = (float)TILE_SIZE / imgH;

                DrawRotaGraph3(
                    (int)(drawX + TILE_SIZE / 2),
                    (int)(drawY + TILE_SIZE / 2),
                    imgW / 2, imgH / 2,
                    scaleX, scaleY,
                    angle,
                    imgStick,
                    TRUE
                );
            }
        }
    }
}
