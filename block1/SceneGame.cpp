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
    _player.collisionDetection(&_enemy);

    _block.collisionDetection(&_enemy);
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
