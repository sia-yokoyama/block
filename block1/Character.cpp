#include "Character.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::setPos(const Vector2Df& pos)
{
    _pos = pos;
}

Vector2Df Character::getPos() const
{
    return _pos;
}

boolean Character::collisionDetection(Vector2Df V_1, Vector2Df V_2, Vector2Df ball)
{
    Vector2Df bar_t = V_1 - V_2;
    Vector2Df lt_ball = ball - V_2;

    double cos_t = bar_t * lt_ball / (bar_t.length() * lt_ball.length());
    double theta = acos(cos_t);
    double len = lt_ball.length() * sin(theta);

    double rt_lt = cos_t * lt_ball.length();
    
    // “–‚½‚è”»’è
    if (len * len <= CHARASIZE * CHARASIZE && (0 <= rt_lt && rt_lt <= bar_t.length())) {
        return true;
    } else {
        return false;
    }
}