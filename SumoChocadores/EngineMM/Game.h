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
class IMPORTEXPORT Game
{
private:
	 Game();
	static Game* Instance;
	LPDIRECT3DDEVICE9 dev;
	HINSTANCE _hInstance;
	HWND hWnd;
public:
	LPDIRECT3DDEVICE9 getDev();
	 ~Game();
	//void Draw();
	void Run(_In_     HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
		_In_ LPTSTR lpCmdLine, _In_     int       nCmdShow,
		ConectorDeEngine* conector);
	 static Game* getInstance();
	 HINSTANCE gethInstance();
	 HWND getHWND();
	//virtual void setMeshes() = 0;
};
