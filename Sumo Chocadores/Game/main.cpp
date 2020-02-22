#include "stdafx.h"
#include <iostream>
#include"../Engine/GameTest.h"
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include "Game.h"

int APIENTRY _tWinMain(_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPTSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	std::cout << "Console works!" << std::endl;

	Game theGame;
	theGame.Run(hInstance, nCmdShow);

	return 0;
}