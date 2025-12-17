#pragma once
class CManager;

class CScene 
{
protected:
    CManager* manager{ nullptr };
public:
    CScene(CManager* pManager) : manager(pManager) {}
    virtual ~CScene() {}

    virtual int Update() { return 0; }
    virtual void Draw() {}
};
