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
    , _blocklist()
{
    for (int i = 0; i < 24; i++){
        _blocklist.push_back(new Block(*this));
    }
}

SceneGame::~SceneGame()
{
}

bool SceneGame::onInit()
{
    _player.setPos(Vector2Df(DWIDTH / 2, DHEIGHT - 100));
    _enemy.setPos(Vector2Df(DWIDTH / 2, DHEIGHT - 106 - (BARSIZE_Y / 2) - CHARASIZE));
    
    int i = 0;
    int j = 0;
    for(auto itr = _blocklist.begin(); itr != _blocklist.end(); ++itr) {
        (*itr)->setPos(Vector2Df(BLOCKSIZE_X * 2 * i + 70, BLOCKSIZE_Y * 2 * j + 100));
        i++;
        if (i >= 8) {
            i = 0;
            j++;
        }
    }

    TaskManager::getInstance().addDrawTask(this, TASK_PRIORITY_SCENE);

    return true;
}

void SceneGame::onRelease()
{
    GameMain::getInstance().changeScene(new SceneTitle()); // SCENE_GAME ÄŠJ
}

void SceneGame::onTick()
{
    _player.onTick();
    _enemy.onTick();

    for(auto itr = _blocklist.begin(); itr != _blocklist.end();) {
        (*itr)->onTick();
        if ((*itr)->collisionDetection(&_enemy)) {
            itr = _blocklist.erase(itr);
            continue;
        }
        itr++;
    }

    if (_enemy.collisionDetectionWall()) {
        kill();
        GameMain::getInstance().getInput().reset();
    }
    _player.collisionDetection(&_enemy);

    if (_blocklist.empty()) {
        kill();
        GameMain::getInstance().getInput().reset();
    }
}

void SceneGame::onDraw(Graphics& g)
{
    _player.onDraw(g);
    _enemy.onDraw(g);
    for(auto itr = _blocklist.begin(); itr != _blocklist.end(); ++itr) {
        (*itr)->onDraw(g);
    }
}

Player&SceneGame::getPlayer()
{
    return _player;
}
