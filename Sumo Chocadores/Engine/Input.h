#ifndef INPUT_H
#define INPUT_H

#include <dinput.h>
#include <map>
#include <vector>
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxguid.lib")
#include "EngineApi.h"
using namespace std;
class IMPORTEXPORT Input
{
private:
	LPDIRECTINPUT8 dip;
	LPDIRECTINPUTDEVICE8 keyDev;
	byte keys[256];
	byte prevKeys[256];
public:
	map<string, vector<int>*>  inputMap;
	Input(HINSTANCE hInstance, HWND hWnd);
	~Input();
	void LoadPrevKeys();
	bool GetKey(string nameOfKey);
	bool GetKeyDown(string nameOfKey);
	bool GetKeyUp(string nameOfKey);
};

#endif