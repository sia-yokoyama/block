#include "GameDefine.h"
#include "SceneGame.h"

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
    GameMain::getInstance().changeScene(new SceneTitle()); // SCENE_GAME çƒäJ
}

void SceneGame::onTick()
{
    _player.onTick();
    _enemy.onTick();

    // ìñÇΩÇËîªíË
    if ((_player.getPos() - _enemy.getPos()).length2() < ((CHARASIZE * CHARASIZE) << 2))
    {
        // è’ìÀ
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
