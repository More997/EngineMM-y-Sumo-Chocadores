#include "stdafx.h"
#include "Textura.h"


Textura::Textura(LPDIRECT3DDEVICE9 dev)
{
	D3DXCreateTextureFromFile(dev,
		L"perfil.jpg",
		&text);
	//dev->SetTexture(0, text);
}

Textura::Textura(LPDIRECT3DDEVICE9 dev, string & newTex)
{
	textname = newTex;
	D3DXCreateTextureFromFile(dev,
		L"yaya.jpg",
		&text);
}


Textura::~Textura()
{
}

IDirect3DTexture9 * Textura::GetText()
{
	return text;
}
