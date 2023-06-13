export module Internal;
export import <cstdlib>;
export import <cstring>;
export import <cmath>;
export import <ctime>;
export import <numbers>;

export namespace gl::detail
{
	using fg_time_t = uint64_t;

	typedef void* FGCBUserData;

	typedef void (*FGCBDisplay)(void);
	typedef void (*FGCBDisplayUC)(FGCBUserData);
	typedef void (*FGCBReshape)(int, int);
	typedef void (*FGCBReshapeUC)(int, int, FGCBUserData);
	typedef void (*FGCBPosition)(int, int);
	typedef void (*FGCBPositionUC)(int, int, FGCBUserData);
	typedef void (*FGCBVisibility)(int);
	typedef void (*FGCBVisibilityUC)(int, FGCBUserData);
	typedef void (*FGCBKeyboard)(unsigned char, int, int);
	typedef void (*FGCBKeyboardUC)(unsigned char, int, int, FGCBUserData);
	typedef void (*FGCBKeyboardUp)(unsigned char, int, int);
	typedef void (*FGCBKeyboardUpUC)(unsigned char, int, int, FGCBUserData);
	typedef void (*FGCBSpecial)(int, int, int);
	typedef void (*FGCBSpecialUC)(int, int, int, FGCBUserData);
	typedef void (*FGCBSpecialUp)(int, int, int);
	typedef void (*FGCBSpecialUpUC)(int, int, int, FGCBUserData);
	typedef void (*FGCBMouse)(int, int, int, int);
	typedef void (*FGCBMouseUC)(int, int, int, int, FGCBUserData);
	typedef void (*FGCBMouseWheel)(int, int, int, int);
	typedef void (*FGCBMouseWheelUC)(int, int, int, int, FGCBUserData);
	typedef void (*FGCBMotion)(int, int);
	typedef void (*FGCBMotionUC)(int, int, FGCBUserData);
	typedef void (*FGCBPassive)(int, int);
	typedef void (*FGCBPassiveUC)(int, int, FGCBUserData);
	typedef void (*FGCBEntry)(int);
	typedef void (*FGCBEntryUC)(int, FGCBUserData);
	typedef void (*FGCBWindowStatus)(int);
	typedef void (*FGCBWindowStatusUC)(int, FGCBUserData);
	typedef void (*FGCBJoystick)(unsigned int, int, int, int);
	typedef void (*FGCBJoystickUC)(unsigned int, int, int, int, FGCBUserData);
	typedef void (*FGCBOverlayDisplay)(void);
	typedef void (*FGCBOverlayDisplayUC)(FGCBUserData);
	typedef void (*FGCBSpaceMotion)(int, int, int);
	typedef void (*FGCBSpaceMotionUC)(int, int, int, FGCBUserData);
	typedef void (*FGCBSpaceRotation)(int, int, int);
	typedef void (*FGCBSpaceRotationUC)(int, int, int, FGCBUserData);
	typedef void (*FGCBSpaceButton)(int, int);
	typedef void (*FGCBSpaceButtonUC)(int, int, FGCBUserData);
	typedef void (*FGCBDials)(int, int);
	typedef void (*FGCBDialsUC)(int, int, FGCBUserData);
	typedef void (*FGCBButtonBox)(int, int);
	typedef void (*FGCBButtonBoxUC)(int, int, FGCBUserData);
	typedef void (*FGCBTabletMotion)(int, int);
	typedef void (*FGCBTabletMotionUC)(int, int, FGCBUserData);
	typedef void (*FGCBTabletButton)(int, int, int, int);
	typedef void (*FGCBTabletButtonUC)(int, int, int, int, FGCBUserData);
	typedef void (*FGCBDestroy)(void);    /* Used for both window and menu destroy callbacks */
	typedef void (*FGCBDestroyUC)(FGCBUserData);

	typedef void (*FGCBMultiEntry)(int, int);
	typedef void (*FGCBMultiEntryUC)(int, int, FGCBUserData);
	typedef void (*FGCBMultiButton)(int, int, int, int, int);
	typedef void (*FGCBMultiButtonUC)(int, int, int, int, int, FGCBUserData);
	typedef void (*FGCBMultiMotion)(int, int, int);
	typedef void (*FGCBMultiMotionUC)(int, int, int, FGCBUserData);
	typedef void (*FGCBMultiPassive)(int, int, int);
	typedef void (*FGCBMultiPassiveUC)(int, int, int, FGCBUserData);

	typedef void (*FGCBInitContext)(void);
	typedef void (*FGCBInitContextUC)(FGCBUserData);
	typedef void (*FGCBAppStatus)(int);
	typedef void (*FGCBAppStatusUC)(int, FGCBUserData);

	/* The global callbacks type definitions */
	typedef void (*FGCBIdle)(void);
	typedef void (*FGCBIdleUC)(FGCBUserData);
	typedef void (*FGCBTimer)(int);
	typedef void (*FGCBTimerUC)(int, FGCBUserData);
	typedef void (*FGCBMenuState)(int);
	typedef void (*FGCBMenuStatus)(int, int, int);
	typedef void (*FGCBMenuStatusUC)(int, int, int, FGCBUserData);

	/* The callback used when creating/using menus */
	typedef void (*FGCBMenu)(int);
	typedef void (*FGCBMenuUC)(int, FGCBUserData);

	/* The FreeGLUT error/warning handler type definition */
	typedef void (*FGError)(const char* fmt, va_list ap);
	typedef void (*FGErrorUC)(const char* fmt, va_list ap, FGCBUserData userData);
	typedef void (*FGWarning)(const char* fmt, va_list ap);
	typedef void (*FGWarningUC)(const char* fmt, va_list ap, FGCBUserData userData);

	/* A list structure */
	struct SFG_List
	{
		void* First;
		void* Last;
	};

	/* A list node structure */
	struct SFG_Node
	{
		void* Next;
		void* Prev;
	};

	/* A helper structure holding two ints and a boolean */
	struct SFG_XYUse
	{
		int X, Y;
		bool Use;
	};

	/// <summary>
	/// An enumeration containing the state of the GLUT execution: initializing, running, or stopping
	/// </summary>
	enum fgExecutionState
	{
		GLUT_EXEC_STATE_INIT,
		GLUT_EXEC_STATE_RUNNING,
		GLUT_EXEC_STATE_STOP
	};

	template<typename T = int>
	inline constexpr T INVALID_MODIFIERS = static_cast<T>(0xFFFFFFFFU);
}
