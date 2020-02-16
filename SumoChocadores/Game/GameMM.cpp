#include "stdafx.h"
#include <iostream>
#include"../Engine/Game.h"
//#include "GranadaGame.h"
//includes for the command window
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "GameTest.h"

int APIENTRY _tWinMain(_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPTSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	std::cout << "Console works!" << std::endl;

	GameTest theGame;
	theGame.Run(hInstance, nCmdShow);

	return 0;
}