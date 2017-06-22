#include "stdafx.h"
#include "Game.h"
#include "Actor.h"

//#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
D3DXMATRIX GetViewMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	D3DXMATRIX transMat;
	D3DXMatrixIdentity(&transMat);
	transMat._41 = -pos.x;
	transMat._42 = -pos.y;
	transMat._43 = -pos.z;

	D3DXMATRIX rotZMat;
	D3DXMatrixIdentity(&rotZMat);
	rotZMat._11 = cos(-rot.z);
	rotZMat._12 = sin(-rot.z);
	rotZMat._21 = -sin(-rot.z);
	rotZMat._22 = cos(-rot.z);

	return transMat * rotZMat;
};
Game::Game()
{
}


Game::~Game()
{
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Game::Run(_In_     HINSTANCE hInstance, _In_     int       nCmdShow) {

	//Creamos la clase de la ventana
	WNDCLASSEX wcex;

	//Iniciamos sus valores en 0
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));


	wcex.cbSize = sizeof(WNDCLASSEX); //Tamaño en bytes
	wcex.style = CS_HREDRAW | CS_VREDRAW; //Estilo de la ventana
	wcex.lpfnWndProc = WndProc; //Funcion de manejo de mensajes de ventana
	wcex.hInstance = hInstance; //Numero de instancia
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //Cursor del mouse
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //Color de fondo
	wcex.lpszClassName = L"GameWindowClass"; //Nombre del tipo (clase) de ventana

											 //Registro mi tipo de ventana en windows
	RegisterClassEx(&wcex);

	//Creo la ventana, recibiendo el numero de ventana
	HWND hWnd = CreateWindowEx(0, //Flags extra de estilo
		L"GameWindowClass", //Nombre del tipo de ventana a crear
		L"Sumos Chocadores", //Titulo de la barra
		WS_OVERLAPPEDWINDOW, //Flags de estilos
		0, //X
		0, //Y
		640, //Ancho
		480, //Alto
		NULL, //Ventana padre
		NULL, //Menu
		hInstance, //Numero de proceso
		NULL); //Flags de multi ventana

	ShowWindow(hWnd, nCmdShow); //Muestro la ventana
	UpdateWindow(hWnd); //La actualizo para que se vea

						//Me comunico con directx por una interfaz, aca la creo
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	//Creo los parametros de los buffers de dibujado (pantalla)
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	//Creo la interfaz con la placa de video
	//LPDIRECT3DDEVICE9 dev;
	HRESULT res =  d3d->CreateDevice(D3DADAPTER_DEFAULT, //Cual placa de vido
		D3DDEVTYPE_HAL, //Soft o hard
		hWnd, //Ventana
		D3DCREATE_HARDWARE_VERTEXPROCESSING, //Proceso de vertices por soft o hard
		&d3dpp, //Los parametros de buffers
		&dev); //El device que se crea

	dev->SetRenderState(D3DRS_LIGHTING, false);

 	Mesh* mesh = new Mesh(dev);
	Actor* Obj = new Actor();
	Actor* Obj1 = new Actor();
	Obj->SetMesh(mesh);
	Obj1->SetMesh(mesh);
	float num = 7.0f;

	while (true)
	{
		MSG msg;

		//Saco un mensaje de la cola de mensajes si es que hay
		//sino continuo
		D3DXMATRIX view = GetViewMatrix(
			D3DXVECTOR3(0, 0, 0),
			D3DXVECTOR3(0, 0, 0));
		D3DXMATRIX projection;
		D3DXMatrixPerspectiveFovLH(
			&projection,
			D3DXToRadian(60),
			(float)640 / 480, //ancho der la pantalla dividido por el alto
			0.0f, //Distancia minima de vision
			50); //Distancia maxima de vision

		dev->SetTransform(D3DTS_VIEW, &view);
		dev->SetTransform(D3DTS_PROJECTION, &projection);
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}
		//Camera* cam = new Camera();
		//float CamPosZ = 0;
		//float CamRotX = 0;
		//Actualizar (Ventana)
		dev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 102, 0), 1.0f, 0);
		dev->BeginScene();
		 
		//TODO: Dibujar objetos
		Obj->setModelPos(-0.5f, -0.25f,5.0f);
		Obj->DrawV(dev);
		Obj1->setModelPos(0.5, -0.25f, num);
		Obj1->setModelRot(num);
		num -= 0.005f;
		Obj1->DrawV(dev);

		dev->EndScene();
		dev->Present(NULL, NULL, NULL, NULL);

		//Release();

	}

	dev->Release();
	d3d->Release();
	delete Obj;
	delete Obj1;
	delete mesh;
}

/*
void Game::Release()
{
	dev->Release();
	vb->Release();
	ind->Release();
	d3d->Release();
}
*/

//Manejo de mensajes por ventana
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		//Si destruyeron esta ventana (cerraron) le pido
		//a windows que cierre la app
		PostQuitMessage(0);
		return 0;
	}

	//Si no maneje el mensaje antes, hago el comportamiento por defecto
	return DefWindowProc(hWnd, message, wParam, lParam);
}
