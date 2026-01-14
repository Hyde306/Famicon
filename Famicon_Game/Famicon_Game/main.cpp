#include "DxLib.h"
#include "Scene_Manager.h"
#include "TitleScene.h"
#include "config.h" 

constexpr auto FPS = 60;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
    SetWaitVSyncFlag(TRUE);
    SetDrawScreen(DX_SCREEN_BACK);

    if (DxLib_Init() == -1) return -1;

    CManager* manager = new CManager();
    manager->ChangeScene(new CTitleScene(manager)); 

    while (ProcessMessage() == 0) 
    {
        ClearDrawScreen();

        manager->Update();
        manager->Draw();

        ScreenFlip();

        WaitTimer(1000 / FPS);

        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
    }

    delete manager;
    DxLib_End();
    return 0;
}
