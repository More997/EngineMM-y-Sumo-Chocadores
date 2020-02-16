#include "stdafx.h"
#include "Input.h"


Input::Input(HINSTANCE hInstance, HWND hWnd)
{
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dip, NULL);

	dip->CreateDevice(GUID_SysKeyboard, &keyDev, NULL);
	keyDev->SetDataFormat(&c_dfDIKeyboard);
	keyDev->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	keyDev->Acquire();
}


Input::~Input()
{
	keyDev->Unacquire();
	keyDev->Release();
	dip->Release();
}

void Input::LoadPrevKeys()
{
	for (int i = 0; i < sizeof(keys); i++)
	{
		prevKeys[i] = keys[i];
	}
	keyDev->GetDeviceState(sizeof(keys), &keys);
}

bool Input::GetKey(string nameOfKey)
{
	for (int i = 0; i < inputMap[nameOfKey]->size(); i++)
	{
		if (keys[inputMap[nameOfKey]->at(i)])
		{
			return true;
		}
	}
	return false;
}

bool Input::GetKeyDown(string nameOfKey)
{
	for (int i = 0; i < inputMap[nameOfKey]->size(); i++)
	{
		if (!prevKeys[inputMap[nameOfKey]->at(i)] && keys[inputMap[nameOfKey]->at(i)])
		{
			return true;
		}
	}
	return false;
}

bool Input::GetKeyUp(string nameOfKey)
{
	for (int i = 0; i < inputMap[nameOfKey]->size(); i++)
	{
		if (prevKeys[inputMap[nameOfKey]->at(i)] && !keys[inputMap[nameOfKey]->at(i)])
		{
			return true;
		}
	}
	return false;
}

