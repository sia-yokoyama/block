#ifndef _GAME_MAIN_H_
#define _GAME_MAIN_H_

#include <windows.h>

#include "Bitmap.h"
#include "Graphics.h"
#include "Input.h"
#include "SceneBase.h"

class GameMain
{
public:
    static GameMain& getInstance();

    virtual bool init(HINSTANCE hInstance);
    virtual void dispose();
    virtual int start();

    virtual void changeScene(SceneBase* newScene);

    virtual Input& getInput();

private:
    HINSTANCE _hInstance;
    WNDCLASS  _winc;
    HWND      _hwnd;

    Bitmap*   _bitmap;
    Graphics* _g;

    Input _in;

    SceneBase* _newScene;

    // �o�b�t�@�f�o�C�X�R���e�L�X�g�Ɋ֘A�t�����Ă����r�b�g�}�b�v�I�u�W�F�N�g
    HGDIOBJ _tmpBitmap;

    GameMain();
    virtual ~GameMain();
    virtual bool _createWindow();
    static LRESULT CALLBACK _wndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    void _resetWindow(Graphics& g); // �f�o�b�O�p

};

#endif // _GAME_MAIN_H_
