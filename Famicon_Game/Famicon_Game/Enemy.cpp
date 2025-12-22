#include "Enemy.h"
#include "DxLib.h"
#include "2D_function.h"
#include <cmath>
#include <vector>
#include <memory>
#include <list>
#include "ChaseEnemy.h"


extern Bomb bomb;

int enemyImg;
static std::vector<std::unique_ptr<BaseEnemy>> enemies;

//==============================
// 敵画像初期化
//==============================
void InitEnemyGraphics()
{
    enemyImg = LoadGraph("image/Enemy1.png");
}

//==============================
// 敵生成
//==============================
void InitEnemies(int map[MAP_HEIGHT][MAP_WIDTH])
{
    enemies.clear();
    auto e = std::make_unique<ChaseEnemy>();
    e->Init(map);
    enemies.push_back(std::move(e));
}

void UpdateEnemies(int map[MAP_HEIGHT][MAP_WIDTH],
    const Player& player,
    Explosion explosions[MAP_HEIGHT][MAP_WIDTH])
{
    for (auto& e : enemies) e->Update(map, player, explosions);
}

void DrawEnemies(float scrollX)
{
    for (auto& e : enemies) e->Draw(scrollX);
}