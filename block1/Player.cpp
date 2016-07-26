#include "Player.h"

#include "GameDefine.h"
#include "GameMain.h"

Player::Player(SceneBase& scene)
    : Character()
    , _scene(scene)
{
}

Player::~Player()
{
}

void Player::onTick()
{
    // Ž©ƒLƒƒƒ‰ˆÚ“®
    Input& in = GameMain::getInstance().getInput();
    if (in.isDown(Input::KEY_LEFT) ) _pos.x = (_pos.x - PLAYER_VELOCITY > 0) ? _pos.x - PLAYER_VELOCITY : 0;
    if (in.isDown(Input::KEY_RIGHT)) _pos.x = (_pos.x + PLAYER_VELOCITY < DWIDTH - 1) ? _pos.x + PLAYER_VELOCITY : DWIDTH - 1;
//    if (in.isDown(Input::KEY_UP)   ) _pos.y = (_pos.y - PLAYER_VELOCITY > 0) ? _pos.y - PLAYER_VELOCITY : 0;
//    if (in.isDown(Input::KEY_DOWN) ) _pos.y = (_pos.y + PLAYER_VELOCITY < DHEIGHT - 1) ? _pos.y + PLAYER_VELOCITY : DHEIGHT - 1;
}

void Player::onDraw(Graphics& g)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,255,0));
    g.setPen(pen);
    g.drawRectangle(_pos.x - BARSIZE_X, _pos.y - BARSIZE_Y, _pos.x + BARSIZE_X, _pos.y + BARSIZE_Y);
    g.setPen(NULL);
    DeleteObject(pen);
}

double Player::getVectorX()
{
    return getPos().x - BARSIZE_X;
}

double Player::getVectorY()
{
    return getPos().y - BARSIZE_Y;
}

void Player::collisionDetection(Enemy *ball)
{
    Vector2Df v_ball = ball->getPos();
    boolean collistion = false;

    Vector2Df bar_lt = getPos() + Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    Vector2Df bar_rt = getPos() + Vector2Df(BARSIZE_X , -BARSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnY();
    }

    bar_lt = getPos() - Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    bar_rt = getPos() - Vector2Df(BARSIZE_X , -BARSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnY();
    }

    bar_lt = getPos() + Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    bar_rt = getPos() + Vector2Df(-BARSIZE_X , BARSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnX();
    }

    bar_lt = getPos() + Vector2Df(BARSIZE_X , -BARSIZE_Y);
    bar_rt = getPos() + Vector2Df(BARSIZE_X , BARSIZE_Y);
    if (Character::collisionDetection(bar_lt, bar_rt, v_ball)) {
        ball->turnX();
    }
}
