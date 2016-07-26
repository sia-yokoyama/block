#include "Block.h"

#include "GameDefine.h"
#include "GameMain.h"

Block::Block(SceneBase& scene)
    : Character()
    , _scene(scene)
{
}

Block::~Block()
{
}

void Block::onTick()
{
}

void Block::onDraw(Graphics& g)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(127,0,127));
    g.setPen(pen);
    g.drawRectangle(_pos.x - BLOCKSIZE_X, _pos.y - BLOCKSIZE_Y, _pos.x + BLOCKSIZE_X, _pos.y + BLOCKSIZE_Y);
    g.setPen(NULL);
    DeleteObject(pen);
}

double Block::getVectorX()
{
    return getPos().x - BLOCKSIZE_X;
}

double Block::getVectorY()
{
    return getPos().y - BLOCKSIZE_Y;
}

boolean Block::collisionDetection(Enemy *ball)
{
    Vector2Df v_ball = ball->getPos();
    boolean collision = false;

    Vector2Df bar_lt = getPos() + Vector2Df(-BLOCKSIZE_X , -BLOCKSIZE_Y);
    Vector2Df bar_rt = getPos() + Vector2Df(BLOCKSIZE_X , -BLOCKSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnY();
        collision = true;
    }

    bar_lt = getPos() - Vector2Df(-BLOCKSIZE_X , -BLOCKSIZE_Y);
    bar_rt = getPos() - Vector2Df(BLOCKSIZE_X , -BLOCKSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnY();
        collision = true;
    }

    bar_lt = getPos() + Vector2Df(-BLOCKSIZE_X , -BLOCKSIZE_Y);
    bar_rt = getPos() + Vector2Df(-BLOCKSIZE_X , BLOCKSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnX();
        collision = true;
    }

    bar_lt = getPos() + Vector2Df(BLOCKSIZE_X , -BLOCKSIZE_Y);
    bar_rt = getPos() + Vector2Df(BLOCKSIZE_X , BLOCKSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnX();
        collision = true;
    }

    return collision;
}
