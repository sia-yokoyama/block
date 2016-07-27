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

    virtual boolean collisionDetectionWall();
    virtual void setCollisionCount(int add_count = 1);

private:
    SceneBase& _scene;
    boolean start_flg;
    int add_x;
    int add_y;
    int collision_count;
    virtual void setTurnX();
    virtual void setTurnY();
};

#endif // _ENEMY_H_
