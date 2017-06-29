#pragma once
#ifndef TEXTURA_H
#define TEXTURA_H
#include <string>
using namespace std;
class Textura
{
private:
	IDirect3DTexture9* text;
	LPWSTR textname;
public:
	Textura(LPDIRECT3DDEVICE9 dev);
	Textura(LPDIRECT3DDEVICE9 dev, LPWSTR newTex);
	~Textura();
	IDirect3DTexture9* GetText();
};
#endif