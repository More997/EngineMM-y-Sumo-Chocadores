#include "stdafx.h"
#include "Texture.h"
#include "Game.h"

Texture::Texture()
{
	Game* s = Game::getInstance();
	D3DXCreateTextureFromFile(s->GetDevice(), //Direct3D Device
		L"grass.jpg", //File name
		&myTexture); //Texture handle //Aca indico en donde se guarda.
					 //dev->SetTexture(0, g_texture);
}
Texture::Texture(LPWSTR comingTexture)
{
	Game* s = Game::getInstance();
	//_textureName = comingTexture;
	D3DXCreateTextureFromFile(s->GetDevice(), //Direct3D Device
		comingTexture, //cambiar
						//(LPCWSTR)textureName.c_str(), //File name
		&myTexture); //Texture handle //Aca indico en donde se guarda.
					 //dev->SetTexture(0, g_texture);
}
void Texture::SetBlend(int blenderElector)
{
	Game* s = Game::getInstance();
	switch (blenderElector)
	{
	case 0:
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		s->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		s->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case 1:
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		s->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		s->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	case 2:
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		s->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		s->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	default:
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}
}
void Texture::SetFiltro(int filtroElector)
{
	Game* s = Game::getInstance();
	switch (filtroElector)
	{
	case 1:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
		break;
	case 2:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_CONVOLUTIONMONO);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_CONVOLUTIONMONO);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_CONVOLUTIONMONO);
		break;
	case 3:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_FORCE_DWORD);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_FORCE_DWORD);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_FORCE_DWORD);
		break;
	case 4:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_GAUSSIANQUAD);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_GAUSSIANQUAD);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_GAUSSIANQUAD);
		break;
	case 5:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		break;
	case 6:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
		break;
	case 7:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_PYRAMIDALQUAD);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_PYRAMIDALQUAD);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_PYRAMIDALQUAD);
		break;
	default:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		break;
	}
}

void Texture::SetWrap(int wrapElector)
{
	Game* s = Game::getInstance();
	switch (wrapElector)
	{
	default:
		break;
	case 1:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		break;
	case 2:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		break;
	case 3:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		break;
	case 4:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_FORCE_DWORD);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_FORCE_DWORD);
		break;
	case 5:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
		break;
	case 6:
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRRORONCE);
		s->GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRRORONCE);
		break;
	}
}
Texture::~Texture()
{
}
IDirect3DTexture9* Texture::GetTexture()
{
	return myTexture;
}