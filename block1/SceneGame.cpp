#include "GameDefine.h"
#include "SceneGame.h"
#include "Vector2D.h"

#include <windows.h>
#include <list>

#include "GameMain.h"
#include "TaskManager.h"
#include "SceneTitle.h"

SceneGame::SceneGame()
    : _player(*this)
    , _enemy(*this)
    , _block(*this)
{
}

SceneGame::~SceneGame()
{
}

bool SceneGame::onInit()
{
    _player.setPos(Vector2Df(DWIDTH / 2, DHEIGHT - 100));
    _enemy.setPos(Vector2Df(DWIDTH / 2, 300));
    _block.setPos(Vector2Df(DWIDTH / 2, 200));

    TaskManager::getInstance().addDrawTask(this, TASK_PRIORITY_SCENE);

    return true;
}

void SceneGame::onRelease()
{
    GameMain::getInstance().changeScene(new SceneTitle()); // SCENE_GAME çƒäJ
}

void SceneGame::onTick()
{
    _player.onTick();
    _enemy.onTick();

    if (_enemy.collisionDetectionWall()) {
        kill();
        GameMain::getInstance().getInput().reset();
    }
//    collisionDetectionBar();
    _player.collisionDetection(&_enemy);
//    collisionDetectionWall();
    collisionDetectionBlock();
}

void SceneGame::onDraw(Graphics& g)
{
    _player.onDraw(g);
    _enemy.onDraw(g);
    _block.onDraw(g);
}

Player&SceneGame::getPlayer()
{
    return _player;
}

void SceneGame::collisionDetectionBar()
{
    Vector2Df bar_lt = _player.getPos() + Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    Vector2Df bar_rt = _player.getPos() + Vector2Df(BARSIZE_X , -BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 2);

    bar_lt = _player.getPos() - Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    bar_rt = _player.getPos() - Vector2Df(BARSIZE_X , -BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 2);

    bar_lt = _player.getPos() + Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    bar_rt = _player.getPos() + Vector2Df(-BARSIZE_X , BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 1);

    bar_lt = _player.getPos() + Vector2Df(BARSIZE_X , -BARSIZE_Y);
    bar_rt = _player.getPos() + Vector2Df(BARSIZE_X , BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 1);
}

void SceneGame::collisionDetectionWall()
{
    Vector2Df wall_lt = Vector2Df(0, DHEIGHT);
    Vector2Df wall_lb = Vector2Df(0, 0);

    collisionDetection(wall_lt, wall_lb, 1);

    wall_lt = Vector2Df(DWIDTH, 0);
    wall_lb = Vector2Df(DWIDTH, DHEIGHT);

    collisionDetection(wall_lt, wall_lb, 1);

    wall_lt = Vector2Df(DWIDTH, 0);
    wall_lb = Vector2Df(0, 0);

    collisionDetection(wall_lt, wall_lb, 2);

    wall_lt = Vector2Df(DWIDTH, DHEIGHT);
    wall_lb = Vector2Df(0, DHEIGHT);

    collisionDetection(wall_lt, wall_lb, 5);
}

void SceneGame::collisionDetectionBlock()
{
    Vector2Df bar_lt = _block.getPos() + Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    Vector2Df bar_rt = _block.getPos() + Vector2Df(BARSIZE_X , -BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 5);

    bar_lt = _block.getPos() - Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    bar_rt = _block.getPos() - Vector2Df(BARSIZE_X , -BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 5);

    bar_lt = _block.getPos() + Vector2Df(-BARSIZE_X , -BARSIZE_Y);
    bar_rt = _block.getPos() + Vector2Df(-BARSIZE_X , BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 5);

    bar_lt = _block.getPos() + Vector2Df(BARSIZE_X , -BARSIZE_Y);
    bar_rt = _block.getPos() + Vector2Df(BARSIZE_X , BARSIZE_Y);

    collisionDetection(bar_lt, bar_rt, 5);
}

void SceneGame::collisionDetection(Vector2Df V_1, Vector2Df V_2, int turn_V)
{
    Vector2Df ball = _enemy.getPos();

    Vector2Df bar_t = V_1 - V_2;
    Vector2Df lt_ball = ball - V_2;

    double cos_t = bar_t * lt_ball / (bar_t.length() * lt_ball.length());
    double theta = acos(cos_t);
    double len = lt_ball.length() * sin(theta);

    double rt_lt = cos_t * lt_ball.length();
    
    // ìñÇΩÇËîªíË
    if (len * len <= CHARASIZE * CHARASIZE && (0 <= rt_lt && rt_lt <= bar_t.length()))
    {
        switch(turn_V) {
        case 1:
            _enemy.turnX();
            break;
        case 2:
            _enemy.turnY();
            break;
        case 5:
            kill();
            GameMain::getInstance().getInput().reset();
            break;
        }

    }

}
