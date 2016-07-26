#include "Block.h"

#include "GameDefine.h"
#include "GameMain.h"

Block::Block(SceneBase& scene)
    : Character()
    , _scene(scene)
{
}

Block::~Block()
{
}

void Block::onTick()
{
}

void Block::onDraw(Graphics& g)
{
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(127,0,127));
    g.setPen(pen);
    g.drawRectangle(_pos.x - BARSIZE_X, _pos.y - BARSIZE_Y, _pos.x + BARSIZE_X, _pos.y + BARSIZE_Y);
    g.setPen(NULL);
    DeleteObject(pen);
}

double Block::getVectorX()
{
    return getPos().x - BARSIZE_X;
}

double Block::getVectorY()
{
    return getPos().y - BARSIZE_Y;
}

