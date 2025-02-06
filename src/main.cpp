
//#######################################################
//                    Platform Globals
//#######################################################
static bool running = true;

//#######################################################
//                    Platform Functions
//#######################################################
bool platform_create_window(int width, int height, char* title);
void platform_update_window();

//#######################################################
//                    Windows Platform
//#######################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>


//#######################################################
//                    Windows Globals
//#######################################################
static HWND window; 


//#######################################################
//                    Platform Implementations
//#######################################################
LRESULT CALLBACK windows_window_callback(HWND window, UINT msg,
                                         WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch(msg)
    {
        case WM_CLOSE:
        {
            running = false;
            break;
        }

        default:
        {
            //let the window handle default input for now
            result = DefWindowProcA(window, msg, wParam, lParam);
        }
    }

    return result;
}

bool platform_create_window(int width, int height, char* title)
{
    HINSTANCE instance = GetModuleHandleA(0);

    WNDCLASSA wc = {};
    wc.hInstance = instance;
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);       //this mean we decide the look of the cursor(arrow)
    wc.lpszClassName = title;                       // this is not the handle just a unique identifier(ID)
    wc.lpfnWndProc = windows_window_callback;       //call back for the input on the window(resize/fullscreen)

    if(!RegisterClassA(&wc))
    {
        return false;
    }

    // WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
    int dwStyle = WS_OVERLAPPEDWINDOW;

     window = CreateWindowExA(0, title,
                                    title,
                                    dwStyle,
                                    100,
                                    100,
                                    width,
                                    height,
                                    NULL,       //parent
                                    NULL,       //menu
                                    instance,
                                    NULL);      //lpParm

    if(window == NULL)
    {
        return false;
    }

    ShowWindow(window, SW_SHOW);

    return true;
}

void platform_update_window()
{
    MSG msg;    

    while(PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg); //call the callback specified when creating the window
    }
}


#endif


int main()
{
    platform_create_window(1200, 720, "celest");

    while(running)
    {
            //update
            platform_update_window();
    }

    return 0;
}










