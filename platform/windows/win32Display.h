#ifndef PLATFORM_WINDOWS_WIN32_DISPLAY_H_
#define PLATFORM_WINDOWS_WIN32_DISPLAY_H_


#include <windows.h>
#include <renderer/interface/RenderDevice.h>
#include <renderer/interface/DisplayInfo.h>
#include <core/error.h>
#include <core/rtl/string.h>
namespace radium
{

///
/// @brief
///     Manages a window on windows
/// 
class win32Display
{
public:

    win32Display();
    ~win32Display();

    /// 
    /// @brief 
    ///     Create a window of size (w,h) at (x,y) with title 'title'
    /// @returns 
    ///     OK if the window was created
    ///     FAILED if the window class failed to register or the window
    ///            could not be created
    /// 
    Status create(int w, int h, int x, int y, const char* title);
    Status create(int w, int h, int x, int y, const rtl::string& title)
    {
        return create(w, h, x, y, title.c_str());
    }

    /// Destroy a window if there is one
    void destroy();

    ///
    /// @brief
    ///     Process and possibly dipatch messages sent to/from the window
    /// 
    void processEvents();

    ///
    /// @brief
    ///     Generate a device config so each respective
    ///     Graphics API can initialize itself
    DisplayInfo& getDisplayInfo();

    /// Show the window
    void show();
    /// Hide the window
    void hide();

private:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    DisplayInfo m_dispInfo;
    WNDCLASSEX m_winfo;

};

} // radium


#endif // PLATFORM_WINDOWS_WIN32_DISPLAY_H_