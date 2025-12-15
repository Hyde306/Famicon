#include "BreakEffect.h"
#include "DxLib.h"
#include "config.h"

static const int BREAK_FRAME_W = 96; 
static const int BREAK_FRAME_H = 96;
static const int BREAK_FRAME_COUNT = 8;

// 壊れエフェクトの更新処理
void UpdateBreakEffects(BreakEffect effects[16])
{
    for (int i = 0; i < 16; i++) 
    {
        if (!effects[i].active) continue;

        effects[i].frameTimer++;

        // 3フレームごとにアニメーションを進める
        if (effects[i].frameTimer >= 3) 
        {
            effects[i].frameTimer = 0;
            effects[i].currentFrame++;
        }

        // 最終フレームを超えたらエフェクト終了
        if (effects[i].currentFrame >= BREAK_FRAME_COUNT) 
        {
            effects[i].active = false;
        }
    }
}

// 描画処理
void DrawBreakEffects(BreakEffect effects[16], float scrollX, int breakImg)
{
    for (int i = 0; i < 16; i++)
    {
        if (!effects[i].active) continue;

        int srcX = effects[i].currentFrame * BREAK_FRAME_W;

        DrawRectExtendGraph
        (
            (int)(effects[i].x - scrollX),
            (int)(effects[i].y),
            (int)(effects[i].x - scrollX + TILE_SIZE),
            (int)(effects[i].y + TILE_SIZE),
            srcX, 0,
            BREAK_FRAME_W, BREAK_FRAME_H,
            breakImg, TRUE
        );
    }
}
