#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Graphics.h"
#include "Vector2D.h"
#include "GameDefine.h"

class Character
{
public:
    Character();
    virtual ~Character();
    virtual void onTick() = 0;
    virtual void onDraw(Graphics& g) = 0;

    virtual void setPos(const Vector2Df& pos);
    virtual Vector2Df getPos() const;
    virtual double getVectorX() = 0;
    virtual double getVectorY() = 0;

    boolean collisionDetection(Vector2Df V_1, Vector2Df V_2, Vector2Df ball);

protected:
    Vector2Df _pos;

private:

};

#endif // _CHARACTER_H_
