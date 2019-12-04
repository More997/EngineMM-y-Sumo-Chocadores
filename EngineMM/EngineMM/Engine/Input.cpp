
#include "stdafx.h"
#include "Input.h"
#include "FVF.h"
//#include <vector>
Input::Input(/*HINSTANCE &hInstance, HWND hWnd*/)
{
	//El DirectImput se inicializa
	Game* s = Game::getInstance();
	DirectInput8Create(s->gethInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dip, NULL);
	//El teclado se inicializa

	dip->CreateDevice(GUID_SysKeyboard, &keyDev, NULL);
	keyDev->SetDataFormat(&c_dfDIKeyboard);
	keyDev->SetCooperativeLevel(s->gethWnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	keyDev->Acquire();

	inputMap["MoveUp"].push_back(DIK_W);
	inputMap["MoveUp"].push_back(DIK_UPARROW);
	
	inputMap["RotateLeft"].push_back(DIK_SPACE);

	inputMap["MoveRight"].push_back(DIK_D);
	inputMap["MoveRight"].push_back(DIK_RIGHTARROW);

	inputMap["MoveLeft"].push_back(DIK_A);
	inputMap["MoveLeft"].push_back(DIK_LEFTARROW);

	inputMap["MoveDown"].push_back(DIK_DOWNARROW);
	inputMap["MoveDown"].push_back(DIK_S);
}
Input::~Input()
{
}
map<string, vector<int>>& Input::GetMap()
{
	return inputMap;
}
bool Input::GetKeyDown(vector<int> *myVectorInt) //Recive por parametro la direccion de memoria del vector de ints del mapa y retorna si se presiona la tecla. 
{
	keyDev->GetDeviceState(sizeof(keys), &keys);
	for (int i = 0; i < myVectorInt->size(); i++)
	{
		int key = myVectorInt->at(i); //es como decir theMap[i]. Pero con punteros se escribe asi.
		if (keys[key])
		{
			lastKey = key;
			return true;
		}
	}
	return false;
}

bool Input::GetKeyUp(vector<int>* myVectorInt)
{
	keyDev->GetDeviceState(sizeof(keys), &keys);
	for (int i = 0; i < myVectorInt->size(); i++)
	{
		int key = myVectorInt->at(i); //es como decir theMap[i]. Pero con punteros se escribe asi.
		if (keys[key])
		{
			return false;
		}
	}
	return true; //Si nunca se entra al if (porque no hay ninguna tecla presionada) se retorna true.
}

int& Input::GetLastKey()
{
	return lastKey;
}
