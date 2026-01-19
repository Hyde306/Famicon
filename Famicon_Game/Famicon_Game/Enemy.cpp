#include "Enemy.h"
#include "DxLib.h"
#include "2D_function.h"
#include <cmath>
#include <vector>
#include <memory>
#include <list>
#include "VerticalEnemy.h"
#include "HorizontalEnemy.h"
#include "ONeillEnemy.h"

extern Bomb bomb;

int enemyImg1;
int enemyImg2;

static std::vector<std::unique_ptr<BaseEnemy>> enemies;
int globalEnemyFrame = 0;
static int enemyAnimTimer = 0;

// 敵画像初期化
void InitEnemyGraphics()
{
    enemyImg1= LoadGraph("image/Enemy1.png");
    enemyImg2= LoadGraph("image/Onill.png");
}

// 敵生成
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH])
{
    enemies.clear();

    enemies.push_back(std::make_unique<ChaseEnemy>());
    enemies.back()->Init(map);

    enemies.push_back(std::make_unique<PatrolEnemy>());
    enemies.back()->Init(map);

    enemies.push_back(std::make_unique<ONeillEnemy>());
    enemies.back()->Init(map);

    globalEnemyFrame = 0;
    enemyAnimTimer = 0;

}

void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],Player& player,Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    for (auto& e : enemies) e->Update(map, player, explosions);
}

void UpdateEnemyAnimation()
{ 
    enemyAnimTimer++;

    if (enemyAnimTimer >= 6) // 通常時アニメーションフレーム
    {
        enemyAnimTimer = 0;
        globalEnemyFrame = (globalEnemyFrame + 1) % NORMAL_FRAME_COUNT;
    }
}

void DrawEnemies(float scrollX)
{
    for (auto& e : enemies) e->Draw(scrollX);
}

bool AllEnemiesDead()
{
    for (auto& e : enemies)
    {
        if (!e->IsDead())
            return false;
    }
    return true;
}
