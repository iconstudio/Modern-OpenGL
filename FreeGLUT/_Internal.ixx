module;
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <tchar.h>
export module Glut.Internal;

typedef struct tagSFG_PlatformDisplay SFG_PlatformDisplay;
struct tagSFG_PlatformDisplay
{
    HINSTANCE       Instance;           /* The application's instance */
    DEVMODE         DisplayMode;        /* Desktop's display settings */
    char* DisplayName;        /* Display name for multi display support*/
};

/*
 * Make "freeglut" window handle and context types so that we don't need so
 * much conditionally-compiled code later in the library.
 */
typedef HWND    SFG_WindowHandleType;
typedef HGLRC   SFG_WindowContextType;
typedef HPALETTE SFG_WindowColormapType;

typedef struct tagSFG_PlatformContext SFG_PlatformContext;
struct tagSFG_PlatformContext
{
    HDC             Device;             /* The window's device context */
};


/* Window's state description. This structure should be kept portable. */
typedef struct tagSFG_PlatformWindowState SFG_PlatformWindowState;
struct tagSFG_PlatformWindowState
{
    RECT            OldRect;            /* window rect     - stored before the window is made fullscreen */
    DWORD           OldStyle;           /* window style    - stored before the window is made fullscreen */
    DWORD           OldStyleEx;         /* window Ex style - stored before the window is made fullscreen */
    BOOL            OldMaximized;       /* window maximized state - stored before the window is made fullscreen */

    BOOL            MouseTracking;      /* Needed for generating GLUT_ENTERED and GLUT_LEFT entry func callbacks on windows */

    /* Need to store window titles to emulate
     * glutSetIconTitle/glutSetWindowTitle as Windows has only
     * one title associated with a window and we need to swap
     * them out based on the window's iconic state
     */
    char* WindowTitle;
    char* IconTitle;
};



/* Joystick-Specific Definitions */
#if !defined(_WIN32_WCE)
#   define _JS_MAX_AXES  8
typedef struct tagSFG_PlatformJoystick SFG_PlatformJoystick;
struct tagSFG_PlatformJoystick
{
    JOYCAPS     jsCaps;
    JOYINFOEX   js;
    UINT        js_id;
};
#endif


/* Menu font and color definitions */
#define  FREEGLUT_MENU_FONT    GLUT_BITMAP_8_BY_13

#define  FREEGLUT_MENU_PEN_FORE_COLORS   {0.0f,  0.0f,  0.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_BACK_COLORS   {0.85f, 0.85f, 0.85f, 1.0f}
#define  FREEGLUT_MENU_PEN_HFORE_COLORS  {1.0f,  1.0f,  1.0f,  1.0f}
#define  FREEGLUT_MENU_PEN_HBACK_COLORS  {0.15f, 0.15f, 0.45f, 1.0f}


/* -- PRIVATE FUNCTION DECLARATIONS ---------------------------------------- */
/* Spaceball device functions, defined in fg_spaceball_mswin.c */
//Added by Jinrong Xie <stonexjr at gmail.com> 12/24/2014
int  fgIsSpaceballWinEvent(HWND hwnd, WPARAM wParam, LPARAM lParam);
void fgSpaceballHandleWinEvent(HWND hwnd, WPARAM wParam, LPARAM lParam);

/* Function to be called on exit */
extern void(__cdecl* __glutExitFunc)(int return_value);
