#include "win32Display.h"

#include <renderer/interface/RenderDevice.h>
#include <windows.h>

using radium::win32Display;
using radium::Status;
using radium::RenderDeviceInitCfg;



LRESULT win32Display::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // TODO needs to be actualyl configured
    return DefWindowProc(hWnd, message, wParam, lParam);
}


win32Display::win32Display()
    : m_instance(nullptr), m_hwnd(nullptr)
{
    ZeroMemory(&m_winfo, sizeof(WNDCLASSEX));
}

win32Display::~win32Display()
{

}

Status win32Display::create(int w, int h, int x, int y, const char* title)
{
    m_instance = (HINSTANCE)GetModuleHandle(NULL);

    m_winfo =
    {
        .cbSize         = sizeof(WNDCLASSEX),
        .style          = CS_HREDRAW | CS_VREDRAW,
        .lpfnWndProc    = win32Display::WndProc,
        .hInstance      = m_instance,
        .hCursor        = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground  = (HBRUSH)COLOR_WINDOW,
        .lpszClassName  = "Win32Window"
    };

    if (!RegisterClassEx(&m_winfo))
        return FAILED;

    m_hwnd = CreateWindowExA(
        NULL,
        "Win32Window",
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        w, h,
        NULL,
        NULL,
        m_instance,
        NULL
    );

    if (!m_hwnd)
    {
        return FAILED;
    }

    UpdateWindow(m_hwnd);

    return OK;
}

void win32Display::destroy()
{
    if (m_hwnd)
    {
        DestroyWindow(m_hwnd);
        UnregisterClassA("Win32Window", m_instance);
        m_hwnd = nullptr;
    }
}

void win32Display::processEvents()
{
    MSG msg;
    while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

RenderDeviceInitCfg win32Display::generateRDConfig()
{
#ifdef RADIUM_API_DX12
    return { m_hwnd, m_instance };
#endif // API
}

void win32Display::show()
{
    assert(m_hwnd);
    ShowWindow(m_hwnd, SW_SHOW);
}

void win32Display::hide()
{
    assert(m_hwnd);
    ShowWindow(m_hwnd, SW_HIDE);
}

