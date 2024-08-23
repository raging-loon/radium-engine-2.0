#include "win32Display.h"

#include <renderer/interface/RenderDevice.h>
#include <windows.h>

using radium::win32Display;
using radium::Status;
using radium::DisplayInfo;



LRESULT win32Display::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO needs to be actualyl configured
    return DefWindowProc(hWnd, message, wParam, lParam);
}


win32Display::win32Display()
{
    m_dispInfo.windowHandle = nullptr;
    m_dispInfo.hInstance = nullptr;
    ZeroMemory(&m_winfo, sizeof(WNDCLASSEX));
}

win32Display::~win32Display()
{

}

Status win32Display::create(int w, int h, int x, int y, const char* title)
{
    m_dispInfo.hInstance = (HINSTANCE)GetModuleHandle(NULL);

    m_winfo =
    {
        .cbSize         = sizeof(WNDCLASSEX),
        .style          = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc    = win32Display::WndProc,
        .hInstance      = m_dispInfo.hInstance,
        .hCursor        = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground  = (HBRUSH)COLOR_WINDOW,
        .lpszClassName  = "Win32Window"
    };

    if (!RegisterClassEx(&m_winfo))
        return FAILED;

    m_dispInfo.windowHandle = CreateWindowExA(
        NULL,
        "Win32Window",
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        w, h,
        NULL,
        NULL,
        m_dispInfo.hInstance,
        NULL
    );

    if (!m_dispInfo.windowHandle)
        return FAILED;
    
    UpdateWindow(m_dispInfo.windowHandle);

    m_dispInfo.wwidth = w;
    m_dispInfo.wheight = h;

    return OK;
}

void win32Display::destroy()
{
    if (m_dispInfo.windowHandle)
    {
        DestroyWindow(m_dispInfo.windowHandle);
        UnregisterClassA("Win32Window", m_dispInfo.hInstance);
        m_dispInfo.windowHandle = nullptr;
    }
}

void win32Display::processEvents()
{
    MSG msg;
    while (PeekMessage(&msg, m_dispInfo.windowHandle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


DisplayInfo& win32Display::getDisplayInfo()
{
    return m_dispInfo;
}

void win32Display::show()
{
    assert(m_dispInfo.windowHandle);
    ShowWindow(m_dispInfo.windowHandle, SW_SHOW);
}

void win32Display::hide()
{
    assert(m_dispInfo.windowHandle);
    ShowWindow(m_dispInfo.windowHandle, SW_HIDE);
}

