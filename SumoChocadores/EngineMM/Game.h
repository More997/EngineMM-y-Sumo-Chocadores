#pragma once
#include "ConectorDeEngine.h" 
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib")
#include <d3dx9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3dx9.lib") //Incluyo la lib a mi proyecto
#include "Vertex.h"
#include "Mesh.h"
#include "Camera.h"
#include "Input.h"
#include "EngineMMAPI.h"
class  Game
{
private:
	IMPORTEXPORT Game();
	static Game* Instance;
	LPDIRECT3DDEVICE9 dev;
public:
	LPDIRECT3DDEVICE9 getDev();
	IMPORTEXPORT ~Game();
	//void Draw();
	IMPORTEXPORT void Run(_In_     HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
		_In_ LPTSTR lpCmdLine, _In_     int       nCmdShow,
		ConectorDeEngine* conector);
	IMPORTEXPORT static Game* getInstance();
	//virtual void setMeshes() = 0;
};
