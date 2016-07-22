#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Character.h"

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

private:
    SceneBase& _scene;

};

#endif // _PLAYER_H_
