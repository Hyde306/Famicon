#pragma once
#include "Scene_Base.h"
#include "Scene_Manager.h"
#include "DxLib.h"
#include "TitleScene.h"

class CClearScene : public CScene
{
public:
    CClearScene(CManager* pManager) : CScene(pManager)
    {
    }

    int Update() override
    {
        // Zキーでタイトルへ戻る
        if (CheckHitKey(KEY_INPUT_Z))
        {
            manager->ChangeScene(new CTitleScene(manager));
        }
        return 0;
    }

    void Draw() override
    {
        DrawString(300, 300, "STAGE 2", GetColor(255, 255, 255));
        DrawString(300, 400, "Z: TITLE", GetColor(255, 255, 0));
    }
};
