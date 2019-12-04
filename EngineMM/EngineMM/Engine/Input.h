#pragma once
#include <iostream>
#include "stdafx.h"
#include <d3dx9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto
#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include "Mesher.h"
#include <map>
#include <vector>
#include "Game.h"
using namespace std;
class IMPORTEXPORT Input
{
private:
	LPDIRECTINPUT8 dip; //DirectImput
	LPDIRECTINPUTDEVICE8 keyDev; //teclado
	map<string, vector<int>> inputMap;
	byte keys[256]; //primer "teclado"
	byte prevKeys[256]; //"teclado" de tecla previa
	int lastKey = 0;
public:
	Input(/* HINSTANCE &hInstance, HWND hWnd*/);
	~Input();
	map<string, vector<int>>& GetMap(); //Retorna la direccion de memoria del mapa
	bool GetKeyDown(vector<int> *myVectorInt);
	bool GetKeyUp(vector<int> *myVectorInt);
	int& GetLastKey(); //tiene que ser constante
};