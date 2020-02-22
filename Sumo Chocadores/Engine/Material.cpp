#include "stdafx.h"
#include "Material.h"

Material::Material(LPCWSTR imageName, LPDIRECT3DDEVICE9 dev)
{
	m_ImageName = imageName;
	D3DXCreateTextureFromFile(dev, getImageName(), &textura);

	dev->SetTexture(0, textura);
}

Material::~Material()
{
}


void Material::SetBlend(LPDIRECT3DDEVICE9 dev, int blendSelector)
{
	dev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	switch (blendSelector)
	{
	case 1:
		//blending aditivo
		dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case 2:
		//blending multiplicativo
		dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		//o sino
		//dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
		//dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		break;
	case 3:
		//alpha blending
		dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	default:
		dev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		break;
	}
}

void Material::SelectBlend(int blend)
{
	m_Blend = blend;
}

void Material::SelectWrap(int wrap)
{
	m_Wrap = wrap;
}

void Material::SelectFiltro(int filtro)
{
	m_Filtro = filtro;
}


int Material::getBlend()
{
	return m_Blend;
}

int Material::getWrap()
{
	return m_Wrap;
}

int Material::getFiltro()
{
	return m_Filtro;
}

void Material::setFiltro(LPDIRECT3DDEVICE9 dev, int filtroSelector)
{
	switch (filtroSelector)
	{
	case 1:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
		break;
	case 2:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_CONVOLUTIONMONO);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_CONVOLUTIONMONO);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_CONVOLUTIONMONO);
		break;
	case 3:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_FORCE_DWORD);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_FORCE_DWORD);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_FORCE_DWORD);
		break;
	case 4:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_GAUSSIANQUAD);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_GAUSSIANQUAD);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_GAUSSIANQUAD);
		break;
	case 5:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		break;
	case 6:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
		break;
	case 7:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_PYRAMIDALQUAD);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_PYRAMIDALQUAD);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_PYRAMIDALQUAD);
		break;

	default:
		dev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		dev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		dev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		break;
	}
}

void Material::setWrap(LPDIRECT3DDEVICE9 dev, int wrapSelector)
{
	switch (wrapSelector)
	{
	default:
		break;
	case 1:
		dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		break;
	case 2:
		dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		break;
	case 3:
		dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		break;
	case 4:
		dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_FORCE_DWORD);
		dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_FORCE_DWORD);
		break;
	case 5:
		dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
		break;
	case 6:
		dev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRRORONCE);
		dev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRRORONCE);
		break;

	}
}

void Material::LoadShader(LPDIRECT3DDEVICE9 dev, LPCWSTR shaderName)
{
	D3DXCreateEffectFromFile(
		dev,
		shaderName,
		NULL,
		NULL,
		D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
		NULL,
		&shader,
		NULL);
}

LPD3DXEFFECT Material::GetShader()
{
	return shader;
}

LPCWSTR Material::getImageName()
{
	return m_ImageName;
}

void Material::Offset(D3DXVECTOR2 trans, float rot, LPDIRECT3DDEVICE9 dev)
{
	D3DXMATRIX transMat2;
	D3DXMatrixIdentity(&transMat2);
	transMat2._31 = trans.x;
	transMat2._32 = trans.y;
	dev->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);


	D3DXMATRIX rotMat2;
	D3DXMatrixIdentity(&rotMat2);
	rotMat2._11 = cos(rot);
	rotMat2._12 = sin(rot);
	rotMat2._21 = -sin(rot);
	rotMat2._22 = cos(rot);
	transMat2 = rotMat2 * transMat2;
	dev->SetTransform(D3DTS_TEXTURE0, &transMat2);
}






