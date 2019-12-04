#pragma once
#include "Mesher.h"
//#include "resource.h"
#include "Actor.h"
#include "Input.h"
#include "GameInterface.h"
class IMPORTEXPORT Game{
private:
	//LPDIRECT3DDEVICE9 dev;
	Game(); //Constructor privado. Singleton.
	static Game* instance;
	HWND hWnd;
	HINSTANCE _hInstance;
/*protected:*/
	Composite* root = new Composite();
public:
	LPDIRECT3DDEVICE9 dev;
	//Input* theInput; //podria ser null. cuidado.
	~Game();
	HWND gethWnd();
	HINSTANCE gethInstance();
	static Game* getInstance();
	LPDIRECT3DDEVICE9 GetDevice();
	virtual void FrameEvent();
	void Run(_In_     HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_     LPTSTR    lpCmdLine,
		_In_     int       nCmdShow, GameInterface* comingInterface);
};