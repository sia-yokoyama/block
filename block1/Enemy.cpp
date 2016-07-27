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
    add_y = -ENEMY_VELOCITY;
    collision_count = 1;
    start_flg = false;
}

Enemy::~Enemy()
{
}

void Enemy::onTick()
{
    if (start_flg == false) {
        Input& in = GameMain::getInstance().getInput();
        if (in.isDown(Input::KEY_LEFT) ) _pos.x = (_pos.x - PLAYER_VELOCITY > 0) ? _pos.x - PLAYER_VELOCITY : 0;
        if (in.isDown(Input::KEY_RIGHT)) _pos.x = (_pos.x + PLAYER_VELOCITY < DWIDTH - 1) ? _pos.x + PLAYER_VELOCITY : DWIDTH - 1;
        if (in.isDown(Input::KEY_UP)   ) start_flg = true;
    } else {
        _pos.x += add_x;
        _pos.y += add_y;
    }
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

void Enemy::setCollisionCount(int add_count)
{
    int before_speed = collision_count / SPEED_UP_COUNT;
    collision_count += add_count;
    int after_speed = collision_count / SPEED_UP_COUNT;
    if (before_speed < after_speed) {
        int add_speed = after_speed - before_speed;
        add_x = (add_x < 0) ? add_x - add_speed : add_x + add_speed;
        add_y = (add_y < 0) ? add_y - add_speed : add_y + add_speed;
    }
}