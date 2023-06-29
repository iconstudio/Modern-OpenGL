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
//#pragma comment (lib, "freeglut.lib")
#else // ^^^ NDEBUG ^^^ // vvv !NDEBUG vvv
//#pragma comment (lib, "freeglutd.lib")
#endif // !NDEBUG
//#pragma comment (lib, "glu32.lib")
#pragma comment (lib, "winmm.lib")

#define EXT_C extern "C"
#define EXT_X extern "C++"

#define IMPORTANT_CLASS(name) class [[nodiscard]] name
#define IMPORTANT_STRUCT(name) struct [[nodiscard]] name
