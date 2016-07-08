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
    // 自キャラ移動
    Input& in = GameMain::getInstance().getInput();
    if (in.isDown(Input::KEY_LEFT) ) _pos.x = (_pos.x - PLAYER_VELOCITY > 0) ? _pos.x - PLAYER_VELOCITY : 0;
    if (in.isDown(Input::KEY_RIGHT)) _pos.x = (_pos.x + PLAYER_VELOCITY < DWIDTH - 1) ? _pos.x + PLAYER_VELOCITY : DWIDTH - 1;
    if (in.isDown(Input::KEY_UP)   ) _pos.y = (_pos.y - PLAYER_VELOCITY > 0) ? _pos.y - PLAYER_VELOCITY : 0;
    if (in.isDown(Input::KEY_DOWN) ) _pos.y = (_pos.y + PLAYER_VELOCITY < DHEIGHT - 1) ? _pos.y + PLAYER_VELOCITY : DHEIGHT - 1;
}

void Player::onDraw(Graphics& g)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,255,0));
    g.setPen(pen);
    g.drawRectangle(_pos.x - CHARASIZE * 3, _pos.y - CHARASIZE / 2, _pos.x + CHARASIZE * 3, _pos.y + CHARASIZE / 2);
    g.setPen(NULL);
    DeleteObject(pen);
}
