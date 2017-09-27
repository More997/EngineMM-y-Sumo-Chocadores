// Juego.cpp: define el punto de entrada de la aplicación.
#include "stdafx.h"
#include "../EngineMM/Game.h"
#include "SumosChocadoresPlay.h"
int APIENTRY _tWinMain(_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPTSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	Game *Play = Game::getInstance();
	SumosChocadoresPlay * SCP = new SumosChocadoresPlay();
	Play->Run(hInstance, hPrevInstance ,lpCmdLine,nCmdShow, SCP);
}
