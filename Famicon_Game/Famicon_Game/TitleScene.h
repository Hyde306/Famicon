#pragma once
#include "Scene_Base.h"
#include "Scene_Manager.h"
#include "game.h"  
#include "DxLib.h"

class CTitleScene : public CScene 
{
private:
    int titleBgImg; // ”wŒi‰æ‘œ

public:
    CTitleScene(CManager* pManager) : CScene(pManager)
    {
        // ‰æ‘œ“Ç‚Ýž‚Ý
        titleBgImg = LoadGraph("image/TitleBack.png");
    }

    ~CTitleScene() 
    {
        DeleteGraph(titleBgImg); // ƒƒ‚ƒŠ‰ð•ú
    }

    int Update() override 
    {
        if (CheckHitKey(KEY_INPUT_RETURN)) 
        {
            manager->ChangeScene(new CGame(manager));
        }
        return 0;
    }

    void Draw() override 
    {
        // ”wŒi‰æ‘œ‚ð•`‰æ
        DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, titleBgImg, TRUE);
        // •¶Žš‚ð•`‰æ
        DrawString(300, 700, "Enter START", GetColor(255, 255, 255));
    }
};
