#include "Enemy.h"

#include "SceneGame.h"

#include <math.h>
#include "GameDefine.h"

Enemy::Enemy(SceneBase& scene)
    : Character()
    , _scene(scene)
{
    add_x = ENEMY_VELOCITY;
    add_y = ENEMY_VELOCITY;
}

Enemy::~Enemy()
{
}

void Enemy::onTick()
{
//    _pos += ((((SceneGame&)_scene).getPlayer().getPos() - _pos).ev() * ENEMY_VELOCITY);
    //setTurnX();
    //setTurnY();
    _pos.x += add_x;
    _pos.y += add_y;
}

void Enemy::onDraw(Graphics& g)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255,0,0));
    g.setPen(pen);
    g.drawEllipse(_pos.x - CHARASIZE, _pos.y - CHARASIZE, _pos.x + CHARASIZE, _pos.y + CHARASIZE);
    g.setPen(NULL);
    DeleteObject(pen);
}

double Enemy::getVectorX()
{
    return getPos().x - CHARASIZE;
}

double Enemy::getVectorY()
{
    return getPos().y - CHARASIZE;
}

void Enemy::setTurnX()
{
    if (getPos().x < CHARASIZE || getPos().x > DWIDTH - CHARASIZE) {
        add_x *= -1;
    }
}

void Enemy::setTurnY()
{
    if (getPos().y < CHARASIZE || getPos().y > DHEIGHT - CHARASIZE) {
        add_y *= -1;
    }
}

void Enemy::turnX()
{
    add_x *= -1;
}

void Enemy::turnY()
{
    add_y *= -1;
}
