#include "stdafx.h"
#include "Textura.h"


Textura::Textura(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateTextureFromFile(dev,
		L"perfil.jpg",
		&text);

}

Textura::Textura(LPDIRECT3DDEVICE9 dev, LPWSTR newTex)
{
	textname = newTex;
	D3DXCreateTextureFromFile(dev,
		newTex,
		&text);
}


Textura::~Textura()
{
}

IDirect3DTexture9 * Textura::GetText()
{
	return text;
}

