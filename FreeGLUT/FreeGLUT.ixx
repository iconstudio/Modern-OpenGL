module;
#include "stdafx.inl"

export module Glut;
export import Glut.DisplayModes;

export namespace glut
{
	void glutInit(int* pargc, char** argv);
	void glutInitWindowPosition(int x, int y);
	void glutInitWindowSize(int width, int height);
	void glutInitDisplayMode(DisplayModes displayMode);
	void glutInitDisplayString(const char* displayMode);
}
