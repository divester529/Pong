#include <windows.h>
#include <gl/gl.h>
#include <stdio.h>
#include "instance.h"

bool running;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
            running=false;
            PostQuitMessage(0);
            break;
        case WM_SIZE:

            break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool initGL(HWND hWnd, HDC* _context, HGLRC* _glContext )
{
    PIXELFORMATDESCRIPTOR pfd; // Device format

    int iFormat;

    *_context = GetDC(hWnd);

    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*_context, &pfd);

    SetPixelFormat(*_context, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *_glContext = wglCreateContext(*_context);

    wglMakeCurrent(*_context, *_glContext);

    glClearColor(0, 0, 0, 0.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 1024, 780, 0, -1, 1);

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1.0f, -1.0f, 1.0f);
    //glMatrixMode(GL_MODELVIEW);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();
    return true;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    running = true;

    HDC deviceContext; // Windows drawing device
    HGLRC glContext; // OpenGL drawing device

    Instance* instance; // Game instance

    WNDCLASS wc = {}; // Window class

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "PongWindowClass";

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0,
                             "PongWindowClass",
                             "Pong",
                             WS_OVERLAPPEDWINDOW^WS_THICKFRAME,
                             CW_USEDEFAULT, CW_USEDEFAULT,
                             1024, 720,
                             NULL,
                             NULL,
                             hInstance,
                             NULL);

    if(hWnd==NULL)
        return 0;

    ShowWindow(hWnd, nCmdShow);

    initGL(hWnd, &deviceContext, &glContext);

    instance = new Instance();

    while(running)
    {
        MSG msg = {};

        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
        }
        if(msg.message == WM_KEYDOWN)
            if(GetKeyState(VK_ESCAPE) & 0x8000)
                running=false;

        instance->getInput(&msg);

        instance->doLogic();

        instance->render();

        SwapBuffers(deviceContext);

        Sleep(1);

    }

    return 0;
}
