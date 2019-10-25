#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
//#include "../EngineMM/Camera.h"
//#include "../EngineMM/Tilemap.h"
#include "../EngineMM/MeshRender.h"
#include "../EngineMM/SceneImporter.h"
#include "../EngineMM/TileRenderer.h"
#include "../EngineMM/Tileset.h"
//#include "../EngineMM/Textura.h"
/*#include "Perseguidor.h"
#include "Jugador.h"*/
class SumosChocadoresPlay :
	public ConectorDeEngine
{
private:
	Composite* comCam;
	Camera* camara;
	LPD3DXEFFECT shaderEffect;
	Game* game;
	float numx = 0;
	float numy = 0;
	float numz = 1.5f;
	Mesh* cosoMesh2;
	Textura* cosoTex2;
	MeshRender* cosoRender2;
	Composite*coso2;
	Mesh* cosoMesh;
	Textura* cosoTex;
	MeshRender* cosoRender;
	Composite*coso;
	Composite* root;
	SceneImporter* sceneImp;
	Tileset* tileSet;
	TileRenderer* tileRender;
	BoundingBox* bbTiles;
	int canttiles;
	int canttiles2;
	BoundingBox bbtest;
	Composite* enemigo;
	Animacion * animacionEnemigo;
	Mesh* meshEnemigo;
	Textura* texEnemigo;
	/*Jugador* pj;
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
