#pragma once
#include "Scene_Base.h"

class CManager
{
public:
    CScene* scene{ nullptr };

    void ChangeScene(CScene* newScene) 
    {
        if (scene) delete scene;
        scene = newScene;
    }

    int Update() { if (scene) scene->Update(); return 0; }
    void Draw() { if (scene) scene->Draw(); }

    ~CManager() { delete scene; }
};
