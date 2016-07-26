#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Character.h"
#include "Enemy.h"

class SceneBase;

class Player : public Character
{
public:
    Player(SceneBase& scene);
    virtual ~Player();

    virtual void onTick();
    virtual void onDraw(Graphics& g);
    virtual double getVectorX();
    virtual double getVectorY();

    virtual void collisionDetection(Enemy *ball);

private:
    SceneBase& _scene;

};

#endif // _PLAYER_H_
