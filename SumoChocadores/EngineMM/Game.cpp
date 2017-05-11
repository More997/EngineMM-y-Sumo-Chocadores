#include "stdafx.h"
#include "Game.h"
#include "Actor.h"

#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
struct Vertex {
	FLOAT x, y, z, rhw;
	DWORD color;
};
Game::Game()
{
}


Game::~Game()
{
}

/*void Game::Draw()
{
	Vertex vertexes[] = {
		{ 0.0f,0.0f,0.0f,1.0f, D3DCOLOR_XRGB(255,0,0) },
		{ 100.0f,0.0f,100.0f,1.0f, D3DCOLOR_XRGB(0,255,0) },
		{ 0.0f,100.0f,0.0f,1.0f, D3DCOLOR_XRGB(0,0,255) },
		{ 100.0f,100.0f,100.0f,1.0f, D3DCOLOR_XRGB(0,255,0) }
	};
	WORD indexes[] = { 0,3,2,0,1,3 };
	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	LPDIRECT3DVERTEXBUFFER9 vb;
	dev->CreateVertexBuffer(4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vb,
		NULL);
	LPDIRECT3DINDEXBUFFER9 ind;
	dev->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&ind,
		NULL);


	VOID *data;
	vb->Lock(0, 0, &data, 0);
	memcpy(data, vertexes, 4 * sizeof(Vertex));
	vb->Unlock();

	ind->Lock(0, 0, &data, 0);
	memcpy(data, indexes, 6 * sizeof(WORD));
	ind->Unlock();
	dev->SetFVF(CUSTOMFVF);
	dev->SetStreamSource(0, vb, 0, sizeof(Vertex));
	//dev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	dev->SetIndices(ind);
	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	/*
	dev->EndScene();
	dev->Present(NULL, NULL, NULL, NULL);
	*/
	/*dev->Release();
	vb->Release();
	ind->Release();
}*/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Game::Run(_In_     HINSTANCE hInstance, _In_     int       nCmdShow) {

	//Creamos la clase de la ventana
	WNDCLASSEX wcex;

	//Iniciamos sus valores en 0
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));


	wcex.cbSize = sizeof(WNDCLASSEX); //Tama�o en bytes
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
	Actor * Obj = new Actor(dev);
	/*Vertex vertexes[] = {
		{0.0f,0.0f,0.0f,1.0f, D3DCOLOR_XRGB(255,0,0)},
		{100.0f,0.0f,100.0f,1.0f, D3DCOLOR_XRGB(0,255,0)},
		{0.0f,100.0f,0.0f,1.0f, D3DCOLOR_XRGB(0,0,255)},
		{100.0f,100.0f,100.0f,1.0f, D3DCOLOR_XRGB(0,0,255)}
	};
	WORD indexes[] = {0,3,2,0,1,3};*/
	


	while (true)
	{
		MSG msg;

		//Saco un mensaje de la cola de mensajes si es que hay
		//sino continuo
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}

		//Actualizar (Ventana)
		dev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 102, 0), 1.0f, 0);
		dev->BeginScene();
		 
		//TODO: Dibujar objetos
		Obj->DrawV(dev);

		dev->EndScene();
		dev->Present(NULL, NULL, NULL, NULL);

		//Release();

	}

	dev->Release();
	d3d->Release();
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
