#include "stdafx.h"
#include "Input.h"





Input::Input(HINSTANCE & hInstance, HWND hWnd)
{
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dip, NULL);

	dip->CreateDevice(GUID_SysKeyboard, &keyDev, NULL);
	keyDev->SetDataFormat(&c_dfDIKeyboard);
	keyDev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	keyDev->Acquire();

	inputMap["Up"].push_back(DIK_W);
	inputMap["Up"].push_back(DIK_UPARROW);

	inputMap["Right"].push_back(DIK_D);
	inputMap["Right"].push_back(DIK_RIGHTARROW);

	inputMap["Left"].push_back(DIK_A);
	inputMap["Left"].push_back(DIK_LEFTARROW);

	inputMap["Down"].push_back(DIK_DOWNARROW);
	inputMap["Down"].push_back(DIK_S);
}

Input::~Input()
{
}

map<string, vector<int>>& Input::GetMap()
{
	return inputMap;
}

bool Input::GetKeyDown(vector<int>* myVectorInt)
{
	keyDev->GetDeviceState(sizeof(keys), &keys);
	for (int i = 0; i < myVectorInt->size(); i++) 
	{
		int key = myVectorInt->at(i);
		if (keys[key])
		{
			keyprev = key;
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
		int key = myVectorInt->at(i);
		if (keys[key])
		{
		return false;
		}
	}
	return true;
}

int & Input::GetLastKey()
{
	return keyprev;
}
