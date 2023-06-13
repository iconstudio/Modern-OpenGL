export module Glut.Window.Definitions;
export import Glut.Types;
export import Glut.Callbacks;

export namespace fg::window
{
	/* This structure holds different freeglut settings */
	typedef struct tagSFG_State SFG_State;
	struct tagSFG_State
	{
		SFG_XYUse        Position;             /* The default windows' position  */
		SFG_XYUse        Size;                 /* The default windows' size      */
		unsigned int     DisplayMode;          /* Display mode for new windows   */

		bool        Initialised;          /* freeglut has been initialised  */

		int              DirectContext;        /* Direct rendering state         */

		bool        ForceIconic;          /* New top windows are iconified  */
		bool        UseCurrentContext;    /* New windows share with current */

		bool        GLDebugSwitch;        /* OpenGL state debugging switch  */
		bool        XSyncSwitch;          /* X11 sync protocol switch       */

		int              KeyRepeat;            /* Global key repeat mode.        */
		int              Modifiers;            /* Current ALT/SHIFT/CTRL state   */

		unsigned           FPSInterval;          /* Interval between FPS printfs   */
		unsigned           SwapCount;            /* Count of glutSwapBuffer calls  */
		unsigned           SwapTime;             /* Time of last SwapBuffers       */

		fg_time_t        Time;                 /* Time that glutInit was called  */
		SFG_List         Timers;               /* The freeglut timer hooks       */
		SFG_List         FreeTimers;           /* The unused timer hooks         */

		FGCBIdleUC       IdleCallback;         /* The global idle callback       */
		FGCBUserData     IdleCallbackData;     /* The global idle callback data  */

		int              ActiveMenus;          /* Num. of currently active menus */
		FGCBMenuState    MenuStateCallback;    /* Menu callbacks are global      */
		FGCBMenuStatusUC MenuStatusCallback;
		FGCBUserData     MenuStatusCallbackData;
		void* MenuFont;             /* Font to be used for newly created menus */

		SFG_XYUse        GameModeSize;         /* Game mode screen's dimensions  */
		int              GameModeDepth;        /* The pixel depth for game mode  */
		int              GameModeRefresh;      /* The refresh rate for game mode */

		int              ActionOnWindowClose;  /* Action when user closes window  */

		fgExecutionState ExecState;            /* Used for GLUT termination       */
		char* ProgramName;          /* Name of the invoking program    */
		bool        JoysticksInitialised; /* Only initialize if application calls for them */
		int              NumActiveJoysticks;   /* Number of active joysticks (callback defined and positive pollrate) -- if zero, don't poll joysticks */
		bool        InputDevsInitialised; /* Only initialize if application calls for them */

		int              MouseWheelTicks;      /* Number of ticks the mouse wheel has turned */

		int              AuxiliaryBufferNumber;/* Number of auxiliary buffers */
		int              SampleNumber;         /*  Number of samples per pixel  */

		bool        SkipStaleMotion;      /* skip stale motion events */

		bool        StrokeFontDrawJoinDots;/* Draw dots between line segments of stroke fonts? */
		bool        AllowNegativeWindowPosition; /* GLUT, by default, doesn't allow negative window positions. Enable it? */

		int              MajorVersion;         /* Major OpenGL context version  */
		int              MinorVersion;         /* Minor OpenGL context version  */
		int              ContextFlags;         /* OpenGL context flags          */
		int              ContextProfile;       /* OpenGL context profile        */
		int              HasOpenGL20;          /* fgInitGL2 could find all OpenGL 2.0 functions */
		FGErrorUC        ErrorFunc;            /* User defined error handler    */
		FGCBUserData     ErrorFuncData;        /* User defined error handler user data */
		FGWarningUC      WarningFunc;          /* User defined warning handler  */
		FGCBUserData     WarningFuncData;      /* User defined warning handler user data */
	};

	/* The structure used by display initialization in fg_init.c */
	typedef struct tagSFG_Display SFG_Display;
	struct tagSFG_Display
	{
		SFG_PlatformDisplay pDisplay;

		int             ScreenWidth;        /* The screen's width in pixels      */
		int             ScreenHeight;       /* The screen's height in pixels     */
		int             ScreenWidthMM;      /* The screen's width in milimeters  */
		int             ScreenHeightMM;     /* The screen's height in milimeters */
	};


	/* The user can create any number of timer hooks */
	typedef struct tagSFG_Timer SFG_Timer;
	struct tagSFG_Timer
	{
		SFG_Node        Node;
		int             ID;                 /* The timer ID integer              */
		FGCBTimerUC     Callback;           /* The timer callback                */
		FGCBUserData    CallbackData;       /* The timer callback user data      */
		fg_time_t       TriggerTime;        /* The timer trigger time            */
	};

	/*
	 * A window and its OpenGL context. The contents of this structure
	 * are highly dependent on the target operating system we aim at...
	 */
	typedef struct tagSFG_Context SFG_Context;
	struct tagSFG_Context
	{
		SFG_WindowHandleType Handle;     /* The window's handle                 */
		SFG_WindowContextType Context;   /* The window's OpenGL/WGL context     */
		SFG_WindowColormapType cmap;     /* The window's colormap/palette */
		int cmap_size;                   /* colormap number of entries */

		SFG_PlatformContext pContext;    /* The window's FBConfig (X11) or device context (Windows) */

		int DoubleBuffered;              /* Treat the window as double-buffered */

		/* When drawing geometry to vertex attribute buffers, user specifies
		 * the attribute indices for vertices, normals and/or texture coords
		 * to freeglut. Those are stored here
		 */
		GLint attribute_v_coord;
		GLint attribute_v_normal;
		GLint attribute_v_texture;
	};


	/*
	 * Bitmasks indicating the different kinds of
	 * actions that can be scheduled for a window.
	 */
#define GLUT_INIT_WORK        (1<<0)
#define GLUT_VISIBILITY_WORK  (1<<1)
#define GLUT_POSITION_WORK    (1<<2)
#define GLUT_SIZE_WORK        (1<<3)
#define GLUT_ZORDER_WORK      (1<<4)
#define GLUT_FULL_SCREEN_WORK (1<<5)
#define GLUT_DISPLAY_WORK     (1<<6)

/*
 * An enumeration containing the desired mapping state of a window
 */
	typedef enum
	{
		DesireHiddenState,
		DesireIconicState,
		DesireNormalState
	} fgDesiredVisibility;

	/*
	 *  There is considerable confusion about the "right thing to
	 *  do" concerning window  size and position.  GLUT itself is
	 *  not consistent between Windows and UNIX/X11; since
	 *  platform independence is a virtue for "freeglut", we
	 *  decided to break with GLUT's behaviour.
	 *
	 *  Under UNIX/X11, it is apparently not possible to get the
	 *  window border sizes in order to subtract them off the
	 *  window's initial position until some time after the window
	 *  has been created.  Therefore we decided on the following
	 *  behaviour, both under Windows and under UNIX/X11:
	 *  - When you create a window with position (x,y) and size
	 *    (w,h), the upper left hand corner of the outside of the
	 *    window is at (x,y) and the size of the drawable area is
	 *    (w,h).
	 *  - When you query the size and position of the window--as
	 *    is happening here for Windows--"freeglut" will return
	 *    the size of the drawable area--the (w,h) that you
	 *    specified when you created the window--and the coordinates
	 *    of the upper left hand corner of the drawable area, i.e.
	 *    of the client rect--which is NOT the (x,y) you specified.
	 */
	typedef struct tagSFG_WindowState SFG_WindowState;
	struct tagSFG_WindowState   /* as per notes above, sizes always refer to the client area (thus without the window decorations) */
	{
		/* window state - size, position, look */
		int             Xpos;               /* Window's top-left of client area, X-coordinate */
		int             Ypos;               /* Window's top-left of client area, Y-coordinate */
		int             Width;              /* Window's width in pixels          */
		int             Height;             /* The same about the height         */
		bool       Visible;            /* Is the window visible now? Not using fgVisibilityState as we only care if visible or not */
		int             Cursor;             /* The currently selected cursor style */
		bool       IsFullscreen;       /* is the window fullscreen?         */

		/* FreeGLUT operations are deferred, that is, window moving, resizing,
		 * Z-order changing, making full screen or not do not happen immediately
		 * upon the user's request, but only in the next iteration of the main
		 * loop, before the display callback is called. This allows multiple
		 * reshape, position, etc requests to be combined into one and is
		 * compatible with the way GLUT does things. Callbacks get triggered
		 * based on the feedback/messages/notifications from the window manager.
		 * Below here we define what work should be done, as well as the relevant
		 * parameters for this work.
		 */
		unsigned int    WorkMask;           /* work (resize, etc) to be done on the window */
		int             DesiredXpos;        /* desired X location */
		int             DesiredYpos;        /* desired Y location */
		int             DesiredWidth;       /* desired window width */
		int             DesiredHeight;      /* desired window height */
		int             DesiredZOrder;      /* desired window Z Order position */
		fgDesiredVisibility DesiredVisibility;/* desired visibility (hidden, iconic, shown/normal) */

		SFG_PlatformWindowState pWState;    /* Window width/height (X11) or rectangle/style (Windows) from before a resize, and other stuff only needed on specific platforms */

		long            JoystickPollRate;   /* The joystick polling rate         */
		fg_time_t       JoystickLastPoll;   /* When the last poll happened       */

		int             MouseX, MouseY;     /* The most recent mouse position    */

		bool       IgnoreKeyRepeat;    /* Whether to ignore key repeat.     */

		bool       VisualizeNormals;   /* When drawing objects, draw vectors representing the normals as well? */
	};


	/*
	 * A generic function pointer.  We should really use the GLUTproc type
	 * defined in freeglut_ext.h, but if we include that header in this file
	 * a bunch of other stuff (font-related) blows up!
	 */
	typedef void (*SFG_Proc)();


	/*
	 * SET_WCB() is used as:
	 *
	 *     SET_WCB( window, cbname, func, udata );
	 *
	 * ...where {window} is the freeglut window to set the callback,
	 *          {cbname} is the window-specific callback to set,
	 *          {func} is a function-pointer,
	 *          {udata} is a void* pointer for user data.
	 *
	 * Originally, {FETCH_WCB( ... ) = func} was rather sloppily used,
	 * but this can cause warnings because the FETCH_WCB() macro type-
	 * casts its result, and a type-cast value shouldn't be an lvalue.
	 *
	 * The {if( FETCH_WCB( ... ) != func )} test is to do type-checking
	 * and for no other reason.  Since it's hidden in the macro, the
	 * ugliness is felt to be rather benign.
	 *
	 * If the function-pointer is the same, the data will be the only
	 * value updated. If the function-pointer changes, the data will
	 * be changed as well, preventing stail data from being passed in.
	 * Just updating the data does nothing unless a function-pointer
	 * exists, as the data is otherwise already allocated.
	 */
#define SET_WCB(window,cbname,func,udata)                      \
do                                                             \
{                                                              \
    if( FETCH_WCB( window, cbname ) != (SFG_Proc)(func) )      \
    {                                                          \
        (((window).CallBacks[WCB_ ## cbname]) = (SFG_Proc)(func)); \
        (((window).CallbackDatas[WCB_ ## cbname]) = (udata));  \
    }                                                          \
    else if( FETCH_USER_DATA_WCB( window, cbname ) != udata )  \
    {                                                          \
        (((window).CallbackDatas[WCB_ ## cbname]) = (udata));  \
    }                                                          \
} while( 0 )

/*
 * FETCH_WCB() is used as:
 *
 *     FETCH_WCB( window, cbname );
 *
 * ...where {window} is the freeglut window to fetch the callback from,
 *          {cbname} is the window-specific callback to fetch.
 *
 * The result is correctly type-cast to the callback function pointer
 * type.
 */
#define FETCH_WCB(window,cbname) \
    ((window).CallBacks[WCB_ ## cbname])

/*
 * FETCH_USER_DATA_WCB() is used as:
 *
 *     FETCH_USER_DATA_WCB( window, cbname );
 *
 * ...where {window} is the freeglut window,
 *          {cbname} is the window-specific callback to be invoked,
 *
 * This expects a variable named "window" of type tagSFG_Window to exist.
 *
 * The result is the callback data pointer.
 */
#define FETCH_USER_DATA_WCB(window,cbname) \
    ((window).CallbackDatas[WCB_ ## cbname])

/*
 * EXPAND_WCB() is used as:
 *
 *     EXPAND_WCB( cbname )(( arg_list, userData ))
 *
 * ... where {(arg_list)} is the parameter list and userData is user
 * provided data.
 *
 * This will take the arg_list and extend it by one argument, adding
 * the argument "userData" to the end of the list.
 *
 * All of this is defined in fg_callback_macros.h
 *
 * See that header for more info.
 *
 * ------------------------------------------------------------------
 */

/*
 * INVOKE_WCB() is used as:
 *
 *     INVOKE_WCB( window, cbname, ( arg_list ) );
 *
 * ...where {window} is the freeglut window,
 *          {cbname} is the window-specific callback to be invoked,
 *          {(arg_list)} is the parameter list.
 *
 * The callback is invoked as:
 *
 *    callback( arg_list, userData );
 *
 * ...where userData is added to the arg_list, but the parentheses
 * are REQUIRED in the {arg_list}.
 *
 * NOTE that it does a sanity-check and also sets the
 * current window.
 *
 */
#define INVOKE_WCB(window,cbname,arg_list)    \
do                                            \
{                                             \
    if( FETCH_WCB( window, cbname ) )         \
    {                                         \
        FGCB ## cbname ## UC func = (FGCB ## cbname ## UC)(FETCH_WCB( window, cbname )); \
        FGCBUserData userData = FETCH_USER_DATA_WCB( window, cbname ); \
        fgSetWindow( &window );               \
        func EXPAND_WCB( cbname )(( arg_list, userData )); \
    }                                         \
} while( 0 )

/*
 * The window callbacks the user can supply us with. Should be kept portable.
 *
 * This enumeration provides the freeglut CallBack numbers.
 * The symbolic constants are indices into a window's array of
 * function callbacks.  The names are formed by splicing a common
 * prefix onto the callback's base name.  (This was originally
 * done so that an early stage of development could live side-by-
 * side with the old callback code.  The old callback code used
 * the bare callback's name as a structure member, so I used a
 * prefix for the array index name.)
 */
	enum
	{
		WCB_Display,
		WCB_Reshape,
		WCB_Position,
		WCB_Keyboard,
		WCB_KeyboardUp,
		WCB_Special,
		WCB_SpecialUp,
		WCB_Mouse,
		WCB_MouseWheel,
		WCB_Motion,
		WCB_Passive,
		WCB_Entry,
		WCB_Visibility,
		WCB_WindowStatus,
		WCB_Joystick,
		WCB_Destroy,

		/* Multi-Pointer X and touch related */
		WCB_MultiEntry,
		WCB_MultiButton,
		WCB_MultiMotion,
		WCB_MultiPassive,

		/* Mobile platforms LifeCycle */
		WCB_InitContext,
		WCB_AppStatus,

		/* Presently ignored */
		WCB_Select,
		WCB_OverlayDisplay,
		WCB_SpaceMotion,     /* presently implemented only on UNIX/X11 and Windows */
		WCB_SpaceRotation,   /* presently implemented only on UNIX/X11 and Windows */
		WCB_SpaceButton,     /* presently implemented only on UNIX/X11 and Windows */
		WCB_Dials,
		WCB_ButtonBox,
		WCB_TabletMotion,
		WCB_TabletButton,

		/* Always make this the LAST one */
		TOTAL_CALLBACKS
	};


	/* This structure holds the OpenGL rendering context for all the menu windows */
	typedef struct tagSFG_MenuContext SFG_MenuContext;
	struct tagSFG_MenuContext
	{
		SFG_WindowContextType MContext;       /* The menu window's WGL context   */
	};

	/* This structure describes a menu */
	typedef struct tagSFG_Window SFG_Window;
	typedef struct tagSFG_MenuEntry SFG_MenuEntry;
	typedef struct tagSFG_Menu SFG_Menu;
	struct tagSFG_Menu
	{
		SFG_Node            Node;
		void* UserData;     /* User data passed back at callback   */
		int                 ID;           /* The global menu ID                  */
		SFG_List            Entries;      /* The menu entries list               */
		FGCBMenuUC          Callback;     /* The menu callback                   */
		FGCBUserData        CallbackData; /* The menu callback user data         */
		FGCBDestroyUC       Destroy;      /* Destruction callback                */
		FGCBUserData        DestroyData;  /* Destruction callback user data      */
		bool           IsActive;     /* Is the menu selected?               */
		void* Font;         /* Font to be used for displaying this menu */
		int                 Width;        /* Menu box width in pixels            */
		int                 Height;       /* Menu box height in pixels           */
		int                 X, Y;         /* Menu box raster position            */

		SFG_MenuEntry* ActiveEntry;  /* Currently active entry in the menu  */
		SFG_Window* Window;       /* Window for menu                     */
		SFG_Window* ParentWindow; /* Window in which the menu is invoked */
	};

	/* This is a menu entry */
	struct tagSFG_MenuEntry
	{
		SFG_Node            Node;
		int                 ID;                     /* The menu entry ID (local) */
		int                 Ordinal;                /* The menu's ordinal number */
		char* Text;                   /* The text to be displayed  */
		SFG_Menu* SubMenu;                /* Optional sub-menu tree    */
		bool           IsActive;               /* Is the entry highlighted? */
		int                 Width;                  /* Label's width in pixels   */
	};

	/*
	 * A window, making part of freeglut windows hierarchy.
	 * Should be kept portable.
	 *
	 * NOTE that ActiveMenu is set to menu itself if the window is a menu.
	 */
	struct tagSFG_Window
	{
		SFG_Node            Node;
		int                 ID;                     /* Window's ID number        */

		SFG_Context         Window;                 /* Window and OpenGL context */
		SFG_WindowState     State;                  /* The window state          */
		SFG_Proc            CallBacks[TOTAL_CALLBACKS]; /* Array of window callbacks */
		FGCBUserData        CallbackDatas[TOTAL_CALLBACKS]; /* Array of window callback datas */
		void* UserData;              /* For use by user           */

		SFG_Menu* Menu[FREEGLUT_MAX_MENUS]; /* Menus appended to window  */
		SFG_Menu* ActiveMenu;             /* The window's active menu  */

		SFG_Window* Parent;                 /* The parent to this window */
		SFG_List            Children;               /* The subwindows d.l. list  */

		bool           IsMenu;                 /* Set to 1 if we are a menu */
	};


	/* A linked list structure of windows */
	typedef struct tagSFG_WindowList SFG_WindowList;
	struct tagSFG_WindowList
	{
		SFG_Node node;
		SFG_Window* window;
	};

	/* This holds information about all the windows, menus etc. */
	typedef struct tagSFG_Structure SFG_Structure;
	struct tagSFG_Structure
	{
		SFG_List        Windows;         /* The global windows list            */
		SFG_List        Menus;           /* The global menus list              */
		SFG_List        WindowsToDestroy;

		SFG_Window* CurrentWindow;   /* The currently set window          */
		SFG_Menu* CurrentMenu;     /* Same, but menu...                 */

		SFG_MenuContext* MenuContext;    /* OpenGL rendering context for menus */

		SFG_Window* GameModeWindow; /* The game mode window               */

		int              WindowID;       /* The window ID for the next window to be created */
		int              MenuID;         /* The menu ID for the next menu to be created */
	};

	/*
	 * This structure is used for the enumeration purposes.
	 * You can easily extend its functionalities by declaring
	 * a structure containing enumerator's contents and custom
	 * data, then casting its pointer to (SFG_Enumerator *).
	 */
	typedef struct tagSFG_Enumerator SFG_Enumerator;
	struct tagSFG_Enumerator
	{
		bool   found;                          /* Used to terminate search  */
		void* data;                           /* Custom data pointer       */
	};
	typedef void (*FGCBWindowEnumerator)(SFG_Window*, SFG_Enumerator*);
	typedef void (*FGCBMenuEnumerator)(SFG_Menu*, SFG_Enumerator*);

	/* The bitmap font structure */
	typedef struct tagSFG_Font SFG_Font;
	struct tagSFG_Font
	{
		char* Name;         /* The source font name             */
		int             Quantity;     /* Number of chars in font          */
		int             Height;       /* Height of the characters         */
		const GLubyte** Characters;   /* The characters mapping           */

		float           xorig, yorig; /* Relative origin of the character */
	};

	/* The stroke font structures */

	typedef struct tagSFG_StrokeVertex SFG_StrokeVertex;
	struct tagSFG_StrokeVertex
	{
		GLfloat         X, Y;
	};

	typedef struct tagSFG_StrokeStrip SFG_StrokeStrip;
	struct tagSFG_StrokeStrip
	{
		int             Number;
		const SFG_StrokeVertex* Vertices;
	};

	typedef struct tagSFG_StrokeChar SFG_StrokeChar;
	struct tagSFG_StrokeChar
	{
		GLfloat         Right;
		int             Number;
		const SFG_StrokeStrip* Strips;
	};

	typedef struct tagSFG_StrokeFont SFG_StrokeFont;
	struct tagSFG_StrokeFont
	{
		char* Name;                       /* The source font name      */
		int             Quantity;                   /* Number of chars in font   */
		GLfloat         Height;                     /* Height of the characters  */
		const SFG_StrokeChar** Characters;          /* The characters mapping    */
	};
}
