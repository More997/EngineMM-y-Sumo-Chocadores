#pragma once
#include "EngineMMAPI.h" 
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib")
#include <d3dx9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto
#include "Vertex.h"
#include "Mesh.h"
#include "Camera.h"
class IMPORTEXPORT Game
{
public:
	LPDIRECT3DDEVICE9 dev;
	Game();
	~Game();
	//void Draw();
	void Run(_In_     HINSTANCE hInstance, _In_     int       nCmdShow);
	//virtual void setMeshes() = 0;
};