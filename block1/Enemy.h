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
    virtual void turnX();
    virtual void turnY();

private:
    SceneBase& _scene;
    int add_x;
    int add_y;
    virtual void setTurnX();
    virtual void setTurnY();
};

#endif // _ENEMY_H_
