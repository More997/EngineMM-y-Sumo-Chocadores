#include "stdafx.h"
#include "Input.h"





Input::Input(/*HINSTANCE & hInstance, HWND hWnd*/)
{
	Game*s = Game::getInstance();
	DirectInput8Create(s->gethInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dip, NULL);
	
	dip->CreateDevice(GUID_SysKeyboard, &keyDev, NULL);
	keyDev->SetDataFormat(&c_dfDIKeyboard);
	keyDev->SetCooperativeLevel(s->getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
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

bool Input::GetKeyDown(vector<int>* vectorinput)
{
	keyDev->GetDeviceState(sizeof(keys), &keys);
	for (int i = 0; i < vectorinput->size(); i++) 
	{
		int key = vectorinput->at(i);
		if (keys[key])
		{
			prevkeys[key] = keys[key];
			return true;
		}
	}
	return false;
}

bool Input::GetKeyUp(vector<int>* vectorinput)
{
	keyDev->GetDeviceState(sizeof(keys), &keys);
	for (int i = 0; i < vectorinput->size(); i++)
	{ 
		int key = vectorinput->at(i);
		if (prevkeys[key]!= keys[key])
		{
		return true;
		}
	}
	return false;
}

