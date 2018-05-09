#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
#include "../EngineMM/Camera.h"
#include "../EngineMM/Tilemap.h"
#include "../EngineMM/MeshRender.h"
#include "Perseguidor.h"
#include "Jugador.h"
class SumosChocadoresPlay :
	public ConectorDeEngine
{
private:
	Composite* comCam;
	Camera* camara;
	float numx = 0;
	float numy = 0;
	float numz = 1.5f;
	Mesh* cosoMesh;
	Textura* cosoTex;
	MeshRender* cosoRender;
	Composite*coso;
	Mesh* cosoMesh2;
	Textura* cosoTex2;
	MeshRender* cosoRender2;
	Composite*coso2;
	/*
	BoundingBox bbtest;
	Perseguidor* enemigo;
	Animacion * animacionEnemigo;
	Mesh* meshEnemigo;
	Textura* texEnemigo;
	Jugador* pj;
	Animacion * animacionPj;
	Mesh* meshPj;
	Textura* texPj;
	bool gameover;
	*/
	Input *gameInput;
	map<string, vector<int>> reciverMap;
	vector<int> *intVectorInputUp;
	vector<int> *intVectorInputLeft;
	vector<int> *intVectorInputRight;
	vector<int> *intVectorInputDown;
	vector<int> *intVectorInputU;
	vector<int> *intVectorInputI;
	//float vel;
	
public:
	SumosChocadoresPlay();
	~SumosChocadoresPlay();
	void Create();
	void Update();
};
#endif
