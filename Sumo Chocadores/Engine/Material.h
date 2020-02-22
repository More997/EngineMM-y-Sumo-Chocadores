#ifndef MATERIAL_H
#define MATERIAL_H

#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include "d3dx9.h"
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto
#include <string>
#include "EngineApi.h"
class IMPORTEXPORT Material
{
private:
	LPCWSTR m_ImageName;
	int m_Blend;
	int m_Wrap;
	int m_Filtro;
	LPD3DXEFFECT shader;
public:
	LPDIRECT3DTEXTURE9 textura;
	Material(LPCWSTR imageName, LPDIRECT3DDEVICE9 dev);
	~Material();
	LPCWSTR getImageName();
	void SetBlend(LPDIRECT3DDEVICE9 dev, int blendSelector);
	void SelectBlend(int blend);
	void SelectWrap(int wrap);
	void SelectFiltro(int filtro);
	void Offset(D3DXVECTOR2 trans, float rot, LPDIRECT3DDEVICE9 dev);
	int getBlend();
	int getWrap();
	int getFiltro();
	void setFiltro(LPDIRECT3DDEVICE9 dev, int filtroSelector);
	void setWrap(LPDIRECT3DDEVICE9 dev, int wrapSelector);
	void LoadShader(LPDIRECT3DDEVICE9 dev, LPCWSTR shaderName);
	LPD3DXEFFECT GetShader();
};

#endif