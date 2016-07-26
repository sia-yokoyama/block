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
    virtual void collisionDetection(Vector2Df V_1, Vector2Df V_2, int turn_V);
    virtual void collisionDetectionBar();
    virtual void collisionDetectionWall();
    virtual void collisionDetectionBlock();

    virtual Player& getPlayer();

private:
    Player _player;
    Enemy  _enemy;
    Block  _block;

};

#endif // _SCENE_GAME_H_
