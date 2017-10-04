#include "stdafx.h"
#include "Textura.h"


Textura::Textura()
{
	Game*d = Game::getInstance();
	D3DXCreateTextureFromFile(d->getDev(),
		L"perfil.jpg",
		&text);
	d->getDev()->SetTexture(0, text);

}

Textura::Textura(LPWSTR newTex)
{
	Game*d = Game::getInstance();
	textname = newTex;
	D3DXCreateTextureFromFile(d->getDev(),
		textname,
		&text);
}


Textura::~Textura()
{
}

IDirect3DTexture9 * Textura::GetText()
{
	return text;
}

