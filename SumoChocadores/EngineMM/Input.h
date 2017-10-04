#pragma once
#include <iostream>
#include "stdafx.h"
#include <d3dx9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto
#include <dinput.h>
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#include "Mesh.h"
#include <map>
#include <vector>
#include "Composite.h"
using namespace std;
class Input :
	public Composite
{
private:
	LPDIRECTINPUT8 dip;
	LPDIRECTINPUTDEVICE8 keyDev;
	map<string, vector<int>> inputMap;
	byte keys[256];
	byte prevkeys[256];
public:
	Input(HINSTANCE &hInstance, HWND hWnd);
	~Input();
	map<string, vector<int>>& GetMap();
	bool GetKeyDown(vector<int>*myVectorInt);
	bool GetKeyUp(vector<int>*myVectorInt);
};

