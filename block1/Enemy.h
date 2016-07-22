#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"

class SceneBase;

class Enemy : public Character
{
public:
    Enemy(SceneBase& scene);
    virtual ~Enemy();

    virtual void onTick();
    virtual void onDraw(Graphics& g);
    virtual double getVectorX();
    virtual double getVectorY();

private:
    SceneBase& _scene;

};

#endif // _ENEMY_H_
