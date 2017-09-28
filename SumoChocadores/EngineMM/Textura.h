#pragma once
#ifndef TEXTURA_H
#define TEXTURA_H
#include <string>
#include "Game.h"
using namespace std;
class Textura
{
private:
	IDirect3DTexture9* text;
	LPWSTR textname;
public:
	IMPORTEXPORT Textura();
	IMPORTEXPORT Textura(LPWSTR newTex);
	IMPORTEXPORT ~Textura();
	IMPORTEXPORT IDirect3DTexture9* GetText();
};
#endif