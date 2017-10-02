#pragma once
#ifndef TEXTURA_H
#define TEXTURA_H
#include <string>
#include "Game.h"
using namespace std;
class IMPORTEXPORT Textura
{
private:
	IDirect3DTexture9* text;
	LPWSTR textname;
public:
	Textura();
	Textura(LPWSTR newTex);
	~Textura();
	IDirect3DTexture9* GetText();
};
#endif