#include "Enemy.h"
#include "GameMain.h"

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

boolean Enemy::collisionDetectionWall()
{
    Vector2Df ball = getPos();

    Vector2Df wall_lt = Vector2Df(0, DHEIGHT);
    Vector2Df wall_lb = Vector2Df(0, 0);
    if (Character::collisionDetection(wall_lt, wall_lb, ball)) {
        turnX();
    }

    wall_lt = Vector2Df(DWIDTH, 0);
    wall_lb = Vector2Df(DWIDTH, DHEIGHT);
    if (Character::collisionDetection(wall_lt, wall_lb, ball)) {
        turnX();
    }

    wall_lt = Vector2Df(DWIDTH, 0);
    wall_lb = Vector2Df(0, 0);
    if (Character::collisionDetection(wall_lt, wall_lb, ball)) {
        turnY();
    }

    wall_lt = Vector2Df(DWIDTH, DHEIGHT);
    wall_lb = Vector2Df(0, DHEIGHT);
    return Character::collisionDetection(wall_lt, wall_lb, ball);
}
