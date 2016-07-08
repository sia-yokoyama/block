#include "GameMain.h"
#include "GameDefine.h"

#include <stdio.h>
#include <math.h>

#include "debug.h"
#include "Fps.h"
#include "TaskManager.h"
#include "SceneTitle.h"

GameMain::GameMain()
    : _hInstance(NULL), _hwnd(NULL)
    , _bitmap(nullptr), _g(nullptr)
    , _newScene(nullptr)
{
}

GameMain::~GameMain()
{
    dispose();
}

GameMain& GameMain::getInstance()
{
    static GameMain self;
    return self;
}

bool GameMain::init(HINSTANCE hInstance)
{
    _hInstance = hInstance;
    if (!_createWindow())
    {
        return false;
    }

    return true;
}

void GameMain::dispose()
{
    if (_g)
    {
        _g->dispose();
        _g = nullptr;
    }
    if (_bitmap)
    {
        _bitmap->dispose();
        _bitmap = nullptr;
    }
}

int GameMain::start()
{
    // ���C�����[�`���J�n
    MSG msg;
    Fps fps(FPS);

    // �ŏ��̃V�[��
    changeScene(new SceneTitle());

    fps.reset();

    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0)) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // �V�[���ύX
            if (_newScene)
            {
                TaskManager::getInstance().addTask((Task*)_newScene, TASK_PRIORITY_SCENE);
                _newScene = nullptr;
            }

            // ���C�����[�`��
            TaskManager::getInstance().onTick();

            // �L�[�A�b�v�𔽉f
            _in.reflectKeyUp();

            // �`�惋�[�`��
            _g->clear(DWIDTH, DHEIGHT);
            TaskManager::getInstance().onDraw(*_g);

            // ��ʍX�V
            InvalidateRect(_hwnd, NULL, FALSE);

            fps.sleep();
        }
    }

    return msg.wParam;;
}

void GameMain::changeScene(SceneBase* newScene)
{
    if (newScene)
    {
        if (_newScene) delete _newScene;
        _newScene = newScene;
    }
}

bool GameMain::_createWindow()
{
    // ���C���E�B���h�E�쐬
    _winc.style         = CS_HREDRAW | CS_VREDRAW;
    _winc.lpfnWndProc   = _wndProc;
    _winc.cbClsExtra    =
    _winc.cbWndExtra    = 0;
    _winc.hInstance     = _hInstance;
    _winc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    _winc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    _winc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    _winc.lpszMenuName  = NULL;
    _winc.lpszClassName = TEXT("Block");
    if (!RegisterClass(&_winc)) return false;

    _hwnd = CreateWindow(
            TEXT("Block"), TEXT("Block"),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, DWIDTH, DHEIGHT, NULL, NULL,
            _hInstance, NULL
        );
    if (!_hwnd) return 0;

    // ��ʃo�b�t�@�̍쐬
    HDC hdc = GetDC(_hwnd);
    if (!hdc) return false;
    _bitmap = new Bitmap(hdc, DWIDTH, DHEIGHT);
    _g = new Graphics(*_bitmap);
    ReleaseDC(_hwnd, hdc);

    // �T�C�Y����
    RECT rc;
    GetClientRect(_hwnd, &rc);
    SetWindowPos(_hwnd, NULL, 0, 0, DWIDTH + DWIDTH - (rc.right - rc.left),
                                   DHEIGHT + DHEIGHT - (rc.bottom - rc.top), SWP_NOMOVE | SWP_NOZORDER);
    ShowWindow(_hwnd, SW_SHOW);

    return true;
}

LRESULT CALLBACK GameMain::_wndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_KEYDOWN:
    case WM_KEYUP:
        {
            //   38
            //37 40 39
            //TRACE("key %c: %ld, rep: %ld, auto: %ld\n", (lp >> 31) ? 'u' : 'd', wp, lp & 0xffff, (lp >> 30) & 1);
            Input& in = getInstance()._in;
            if (msg == WM_KEYDOWN)
            {
                in.keyRepeat(wp);
                if (!(lp & 0x40000000)) // �I�[�g���s�[�g
                {
                    in.keyDown(wp);
                }
            }
            else
            {
                in.keyUp(wp);
            }
            //TRACE("key d: %d, r: %d, u: %d\n", input[INPUT_DOWN], input[INPUT_REP], input[INPUT_UP]);
        }
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd , &ps);

            Graphics* gsrc = getInstance()._g;
            if (gsrc)
            {
                Graphics g(hdc);
                RECT rc;
                GetClientRect(hwnd , &rc);
                int w = rc.right - rc.left, h = rc.bottom - rc.top;
                if (w == DWIDTH && h == DHEIGHT && 0)
                {
                    g.copy(*gsrc, 0, 0, w, h, 0, 0);
                }
                else
                {
                    g.copy(*gsrc, 0, 0, w, h, 0, 0, DWIDTH, DHEIGHT);
                }

                getInstance()._resetWindow(g);
            }

            EndPaint(hwnd , &ps);
        }
        return 0;
    case WM_DESTROY:
        //MessageBox(hwnd, TEXT("�I�����܂�"), TEXT("Block"), MB_ICONINFORMATION);
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

void GameMain::_resetWindow(Graphics& g)
{
    // ���̓e�X�g
    g.setTextColor(255, 255, 255);
    char testBuf[5];
    sprintf(testBuf, "%c%c%c%c", _in.isDown(Input::KEY_LEFT)?'<':' ', _in.isDown(Input::KEY_UP)?'^':' ', _in.isDown(Input::KEY_DOWN)?'v':' ', _in.isDown(Input::KEY_RIGHT)?'>':' ');
    g.drawString(10, 10, testBuf);
    sprintf(testBuf, "%c%c%c%c", _in.isRepeat(Input::KEY_LEFT)?'<':' ', _in.isRepeat(Input::KEY_UP)?'^':' ', _in.isRepeat(Input::KEY_DOWN)?'v':' ', _in.isRepeat(Input::KEY_RIGHT)?'>':' ');
    g.drawString(10, 30, testBuf);
    //TextOut(hdc, 10, 10, TEXT("test"), lstrlen(TEXT("test")));
}

Input& GameMain::getInput()
{
    return _in;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    GameMain& gmain = GameMain::getInstance();
    if (!gmain.init(hInstance))
    {
        return 0;
    }

    int status = gmain.start();

    gmain.dispose();

    return status;
}
