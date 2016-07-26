#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

#include "SceneBase.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"

class SceneGame : public SceneBase
{
public:
    SceneGame();
    virtual ~SceneGame();
    virtual bool onInit();
    virtual void onRelease();
    virtual void onTick();
    virtual void onDraw(Graphics& g);

    virtual Player& getPlayer();

private:
    Player _player;
    Enemy  _enemy;
    Block  _block;

};

#endif // _SCENE_GAME_H_
