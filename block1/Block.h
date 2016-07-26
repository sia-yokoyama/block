#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Character.h"
#include "Enemy.h"

class SceneBase;

class Block : public Character
{
public:
    Block(SceneBase& scene);
    virtual ~Block();

    virtual void onTick();
    virtual void onDraw(Graphics& g);
    virtual double getVectorX();
    virtual double getVectorY();

    virtual boolean collisionDetection(Enemy *ball);

private:
    SceneBase& _scene;

};

#endif // _BLOCK_H_
