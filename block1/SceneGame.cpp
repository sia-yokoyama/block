#include "GameDefine.h"
#include "SceneGame.h"
#include "Vector2D.h"

#include <windows.h>

#include "GameMain.h"
#include "TaskManager.h"
#include "SceneTitle.h"

SceneGame::SceneGame()
    : _player(*this)
    , _enemy(*this)
{
}

SceneGame::~SceneGame()
{
}

bool SceneGame::onInit()
{
    _player.setPos(Vector2Df(DWIDTH / 2, DHEIGHT - 100));
    _enemy.setPos(Vector2Df(DWIDTH / 2, 100));

    TaskManager::getInstance().addDrawTask(this, TASK_PRIORITY_SCENE);

    return true;
}

void SceneGame::onRelease()
{
    GameMain::getInstance().changeScene(new SceneTitle()); // SCENE_GAME �ĊJ
}

void SceneGame::onTick()
{
    _player.onTick();
    _enemy.onTick();

    Vector2Df bar_lt = _player.getPos() + Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    Vector2Df bar_rt = _player.getPos() + Vector2Df(BARSIZE_X , -BARSIZE_Y);
    Vector2Df ball = _enemy.getPos();

    Vector2Df bar_t = bar_rt - bar_lt;
    Vector2Df lt_ball = ball - bar_lt;

    //double x = bar.length();
    //double a = bar.operator*(enemy) / bar.length();
    //double b = (bar.operator*(enemy) * bar.operator*(enemy)) / bar.length();
    //double c = enemy.length() - b;
    //double y = CHARASIZE * CHARASIZE;

    double cos_t = bar_t * lt_ball / (bar_t.length() * lt_ball.length());
    double theta = acos(cos_t);
    double len = lt_ball.length() * sin(theta);

    double rt_lt = cos_t * lt_ball.length();
    
    // �����蔻��
    if (len <= CHARASIZE && (0 <= rt_lt && rt_lt <= bar_t.length()))
    {
        // �Փ�
        kill();
        GameMain::getInstance().getInput().reset();
    }
}

void SceneGame::onDraw(Graphics& g)
{
    _player.onDraw(g);
    _enemy.onDraw(g);
}

Player&SceneGame::getPlayer()
{
    return _player;
}
