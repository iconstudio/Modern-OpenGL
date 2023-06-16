#pragma once
#ifndef NOMINMAX
#define NOMINMAX
#endif // NOMINMAX

#define FGAPIENTRY __stdcall
#if defined(FREEGLUT_EXPORTS)
#define FGAPI __declspec(dllexport)
#else // ^^^ defined(FREEGLUT_EXPORTS) ^^^ // vvv !defined(FREEGLUT_EXPORTS) vvv
#define FGAPI __declspec(dllimport)
#endif // !defined(FREEGLUT_EXPORTS)

#ifdef NDEBUG
#pragma comment (lib, "freeglut.lib")
#else // ^^^ NDEBUG ^^^ // vvv !NDEBUG vvv
#pragma comment (lib, "freeglutd.lib")
#endif // !NDEBUG
#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "opengl32.lib")
//#pragma comment (lib, "gdi32.lib")
//#pragma comment (lib, "winmm.lib")
//#pragma comment (lib, "user32.lib")
