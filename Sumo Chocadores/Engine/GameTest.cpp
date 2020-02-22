#include "stdafx.h"
#include "GameTest.h"
#include "Model.h"
#include "Camera.h"
#include "d3dx9.h"
#include "MeshRenderer.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

GameTest::GameTest()
{
}

GameTest::~GameTest()
{
	m_Input->~Input();
}

void GameTest::Run(HINSTANCE hInstance, int nCmdShow)
{
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
		L"Title", //Titulo de la barra
		WS_OVERLAPPEDWINDOW, //Flags de estilos
		600, //X
		100, //Y
		640, //Ancho
		480, //Alto
		NULL, //Ventana padre
		NULL, //Menu
		hInstance, //Numero de proceso
		NULL); //Flags de multi ventana

	ShowWindow(hWnd, nCmdShow); //Muestro la ventana
	UpdateWindow(hWnd); //La actualizo para que se vea

						//Creo la interfaz con la placa de video
	LPDIRECT3DDEVICE9 dev;

	//Me comunico con directx por una interfaz, aca la creo
	LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);

	//Creo los parametros de los buffers de dibujado (pantalla)
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3d->CreateDevice(D3DADAPTER_DEFAULT, //Cual placa de vido
		D3DDEVTYPE_HAL, //Soft o hard
		hWnd, //Ventana
		D3DCREATE_HARDWARE_VERTEXPROCESSING, //Proceso de vertices por soft o hard
		&d3dpp, //Los parametros de buffers
		&dev); //El device que se crea.

	m_Input = new Input(hInstance, hWnd);
	LoadContent(dev);

	float actualMs = 0;

	while (true)
	{

		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}

		//Actualizar
		dev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 250, 100), 1.0f, 0);
		dev->BeginScene();

		//-------------------------------------------------------------------------------------

		m_Input->LoadPrevKeys();

		Update(dev);
		root->Update();


		bsp->CheckTree(camera->m_Transform, root); // Comprueba si los objetos estan entre los planos*/

		list<Composite*> objectsToDraw = bsp->GetObjectsToDraw();

		for (unsigned int i = 0; i < bsp->planos.size(); i++)
		{
			bsp->planos.at(i)->Draw(dev, frustum, false);
		}

		for (std::list<Composite*>::iterator i = objectsToDraw.begin(); i != objectsToDraw.end(); i++)
		{
			(*i)->Draw(dev, frustum, false);
		}

		dev->EndScene();
		dev->Present(NULL, NULL, NULL, NULL);

	}

	d3d->Release();
	dev->Release();
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}