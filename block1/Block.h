#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Character.h"

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

private:
    SceneBase& _scene;

};

#endif // _BLOCK_H_
