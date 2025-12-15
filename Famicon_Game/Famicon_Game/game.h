//ゲームシーンヘッダ
#pragma once
#include "objBase.h"
#include "CCamera.h"

extern int bombImg;
extern int breakImg;
extern int breakeffect;
extern int imgSmallCenter;
extern int imgBigCenter;
extern int imgSmallStick;
extern int imgBigStick;

class CGame :public CScene
{
private:

public:
	vector<unique_ptr<BaseVector>> base;

	//コンストラクタ
	CGame(CManager*);

	//デストラクタ
	~CGame();

	int Update();//更新処理
	void UpdateScroll();//横スクロール
	void DrawBomb();//ボム描画
	void DrawExplosionTile(int x, int y, int dir, bool big, float scrollX);
	void Draw();//描画
};