#pragma once
#include <string>
using namespace std;
class IMPORTEXPORT Texture
{
private:
	IDirect3DTexture9* myTexture;
	//LPWSTR _textureName;
public:
	Texture();
	Texture(LPWSTR comingTexture);
	~Texture();
	IDirect3DTexture9* GetTexture();
	void SetBlend(int blenderElector);
	void SetFiltro(int filtroElector);
	void SetWrap(int wrapElector);
};