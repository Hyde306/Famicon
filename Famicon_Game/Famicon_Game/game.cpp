#include "DxLib.h"
#include "Scene_Manager.h"
#include "game.h"
#include "function.h"
#include "config.h"
#include "Map.h"
#include "Player.h"
#include "Bomb.h"
#include "Explosion.h"
#include "BreakEffect.h"
#include "Enemy.h"

Player player;
Bomb bomb;
BreakEffect breakEffects[16];

float scrollX = 0.0f;

// 画像
int bombImg;
int breakImg;
int breakeffect;
int imgSmallCenter;
int imgBigCenter;
int imgSmallStick;
int imgBigStick;

// コンストラクタ
CGame::CGame(CManager* p) : CScene(p)
{
    InitMapGraphics();
    player.Init();
    InitExplosions(explosions);

    // 爆弾初期化
    bomb.active = false;

    // 画像読み込み（ここでまとめてロード）
    imgSmallCenter = LoadGraph("image/SmallCenter.png");
    imgBigCenter = LoadGraph("image/BigCenter.png");
    imgSmallStick = LoadGraph("image/SmallStick.png");
    imgBigStick = LoadGraph("image/BigStick.png");

    bombImg = LoadGraph("image/Bomb.png");
    breakImg = LoadGraph("image/Break.png");
    breakeffect = LoadGraph("image/breakImg.png");

    InitEnemyGraphics();
    InitEnemies(map);
}

// 更新処理
int CGame::Update()
{
    player.Update(map, explosions);
    bomb.Update(explosions, map, breakEffects);
    UpdateScroll();

    if (player.WantsToPlaceBomb() && !bomb.active)
    {
        bomb.Place(player.GetMapX(), player.GetMapY());
    }

    UpdateExplosion(explosions);
    UpdateBreakEffects(breakEffects);
    UpdateEnemies(map, player, explosions);
    return 0;
}

// スクロール制御
void CGame::UpdateScroll()
{
    float playerCenter = player.GetCenterX();
    float targetScrollX = playerCenter - (WINDOW_WIDTH / 2.0f);
    scrollX += (targetScrollX - scrollX) * 0.2f;
    float maxScroll = MAP_WIDTH * TILE_SIZE - WINDOW_WIDTH;
    if (scrollX < 0) scrollX = 0;
    if (scrollX > maxScroll) scrollX = maxScroll;
}

// 爆弾描画
void CGame::DrawBomb()
{
    if (!bomb.active) return;

    int frameWidth = 814 / 3;
    int srcX = bomb.currentFrame * frameWidth;

    float drawX = bomb.mapX * TILE_SIZE - scrollX;
    float drawY = bomb.mapY * TILE_SIZE;

    DrawRectExtendGraph(
        (int)drawX, (int)drawY,
        (int)(drawX + TILE_SIZE), (int)(drawY + TILE_SIZE),
        srcX, 0, frameWidth, 272,
        bombImg, TRUE
    );
}

void CGame::DrawExplosionTile(int x, int y, int dir, bool big, float scrollX)
{
    int cx = x * TILE_SIZE - scrollX;
    int cy = y * TILE_SIZE;

    int imgCenter;
    int imgStick;

    if (big) {
        imgCenter = imgBigCenter;
        imgStick = imgBigStick;
    }
    else {
        imgCenter = imgSmallCenter;
        imgStick = imgSmallStick;
    }

    if (dir == 0) {
        DrawExtendGraph(cx, cy, cx + TILE_SIZE, cy + TILE_SIZE, imgCenter, TRUE);
        return;
    }

    int angle = 0;
    switch (dir) {
    case 1: angle = 0;   break; // 上
    case 2: angle = 180; break; // 下
    case 3: angle = 270; break; // 左
    case 4: angle = 90;  break; // 右
    }

    DrawRotaGraph2(
        cx + TILE_SIZE / 2,
        cy + TILE_SIZE / 2,
        0, 0,
        1.0,
        angle * DX_PI / 180.0,
        imgStick,
        TRUE
    );
}

void CGame::Draw()
{
    ClearDrawScreen();
    DrawMap(scrollX);
    DrawBomb();
    DrawExplosion(explosions, scrollX,
        imgSmallCenter, imgBigCenter,
        imgSmallStick, imgBigStick);
    DrawBreakEffects(breakEffects, scrollX, breakeffect);
    player.Draw(scrollX);

    DrawEnemies(scrollX);
    ScreenFlip();
}

CGame::~CGame() {}
