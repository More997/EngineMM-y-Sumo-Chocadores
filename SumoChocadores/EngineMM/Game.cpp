#include "stdafx.h"
#include "Game.h"
#include "Actor.h"
#include "Textura.h"
Game::Game()
{
}


Game::~Game()
{
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void Game::Run(_In_     HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_     int       nCmdShow) {

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
	HRESULT res = d3d->CreateDevice(D3DADAPTER_DEFAULT, //Cual placa de vido
		D3DDEVTYPE_HAL, //Soft o hard
		hWnd, //Ventana
		D3DCREATE_HARDWARE_VERTEXPROCESSING, //Proceso de vertices por soft o hard
		&d3dpp, //Los parametros de buffers
		&dev); //El device que se crea

	dev->SetRenderState(D3DRS_LIGHTING, FALSE);
	Mesh* mesh = new Mesh(dev);
	Textura* Tex = new Textura(dev);
	Textura* Tex2 = new Textura(dev, L"yaya.jpg");
	Textura* Tex3 = new Textura(dev, L"tem.png");
	Actor* Obj = new Actor(Tex);
	Obj->SetMesh(mesh);
	Actor* Obj1 = new Actor(Tex2);
	Obj1->SetMesh(mesh);
	Actor* Obj3 = new Actor(Tex);
	Obj3->SetMesh(mesh);
	Actor* Per = new Actor(Tex); //perseguido
	Per->SetMesh(mesh);
	Actor* Cap = new Actor(Tex3); //Captura!
	Cap->SetMesh(mesh);
	Actor* rotY = new Actor(Tex2); 
	rotY->SetMesh(mesh);
	Camera* Cam = new Camera();
	Cap->setModelPos(-2, 2, 5);	
	Obj3->setModelPos(0.5f, -0.25f, 5);
	float numx = 2;
	float numy = 1;
	float num = 7.0f;
	float num2 = -5.0f;
	Input *inputKey = new Input(hInstance, hWnd);
	map<string, vector<int>> map = inputKey->GetMap();
	vector<int> *vUp = &map["Up"];
	vector<int> *vLeft = &map["Left"];
	vector<int> *vRight = &map["Right"];
	vector<int> *vDown = &map["Down"];
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
		Cam->update(dev);
		
		if (inputKey->GetKeyDown(vUp) == true)
			numy += 0.1;
		if (inputKey->GetKeyDown(vDown) == true)
			numy -= 0.1;
		if (inputKey->GetKeyDown(vLeft) == true)
			numx -= 0.1;
		if (inputKey->GetKeyDown(vRight) == true)
			numx += 0.1;
		Per->setModelPos(numx, numy, 5);
		D3DXVECTOR3 diff = Per->getVector() - Cap->getVector();
		float distance = D3DXVec3Length(&diff);
		D3DXVECTOR3 dir = diff / distance;
		D3DXVECTOR3 pos = Cap->getVector();
			Cap->setVector(pos + (dir*0.01f));
			diff = Obj->getVector() - Obj3->getVector();
			distance = D3DXVec3Length(&diff);
		    dir = diff / distance;
			pos = Obj3->getVector();
			Obj3->setVector(pos - (dir*0.001f));

		Per->DrawV(dev,1); //Se mueve con el Input
		Cap->DrawV(dev, 2); //Persigue a Per
		Obj->setModelPos(num2, -0.25f,5); //Se mueve a la derecha
		rotY->setModelPos(1, 1.0f, 5); //Se mueve a la derecha
		Obj1->setModelPos(0.5, -0.25f, num); //gira
		Obj1->setModelRotZ(num);
		rotY->setModelRotY(num); //Rota en Y
		num += 0.005f;
		num2 += 0.005f;
		rotY->DrawV(dev, 1);
		Obj->DrawV(dev,0);
		Obj1->DrawV(dev,1);
		Obj3->DrawV(dev, 5); //huye de Obj
		dev->EndScene();
		dev->Present(NULL, NULL, NULL, NULL);
	}

	dev->Release();
	d3d->Release();
	delete Obj;
	delete Obj1;
	delete Obj3;
	delete Per;
	delete Cap;
	delete mesh;
	delete Cam;
	delete Tex;
	delete Tex2;
}



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
