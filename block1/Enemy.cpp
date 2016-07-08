#include "Enemy.h"

#include "SceneGame.h"

#include <math.h>
#include "GameDefine.h"

Enemy::Enemy(SceneBase& scene)
    : Character()
    , _scene(scene)
{
}

Enemy::~Enemy()
{
}

void Enemy::onTick()
{
//    _pos += ((((SceneGame&)_scene).getPlayer().getPos() - _pos).ev() * ENEMY_VELOCITY);
}

void Enemy::onDraw(Graphics& g)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255,0,0));
    g.setPen(pen);
    g.drawEllipse(_pos.x - CHARASIZE, _pos.y - CHARASIZE, _pos.x + CHARASIZE, _pos.y + CHARASIZE);
    g.setPen(NULL);
    DeleteObject(pen);
}
