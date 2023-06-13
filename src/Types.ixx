export module Glut.Types;

export namespace fg
{
	using fg_time_t = unsigned long long;
	using FGCBUserData = void*;

	/// <summary>
	/// A list structure
	/// </summary>
	struct SFG_List
	{
		void* First;
		void* Last;
	};

	/// <summary>
	/// A list node structure
	/// </summary>
	struct SFG_Node
	{
		void* Next;
		void* Prev;
	};

	/// <summary>
	/// A helper structure holding two ints and a boolean
	/// </summary>
	struct SFG_XYUse
	{
		int X, Y;
		bool Use;
	};

	/// <summary>
	/// An enumeration containing the state of the GLUT execution:
	/// initializing, running, or stopping
	/// </summary>
	enum fgExecutionState
	{
		GLUT_EXEC_STATE_INIT,
		GLUT_EXEC_STATE_RUNNING,
		GLUT_EXEC_STATE_STOP
	};
}
