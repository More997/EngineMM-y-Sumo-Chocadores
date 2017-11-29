#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
#include "../EngineMM/Camera.h"
#include "../EngineMM/Tilemap.h"
#include "../EngineMM/MeshRender.h"
class SumosChocadoresPlay :
	 public ConectorDeEngine
{
private:
	Camera* camara;
	bool achicar = false;
	float num = 0;
	float num2 = 0;
	Mesh* cosoMesh;
	Textura* cosoTex;
	MeshRender* cosoRender;
	Composite*coso;
	BoundingBox* bbtest;
/*
	Animacion * sumoAnima;
	Composite* sumo;
	Mesh* sumoMesh;
//	MeshRender* sumoRender;
	Textura* sumoTex;
	Composite* tiles;
	Tilemap*  tilesMap;
	Mesh* tileMesh;
	MeshRender* tileRender;
	Composite* tiles2;
	Tilemap* tilesMap2;
	Mesh* tileMesh2;
	MeshRender* tileRender2;
	vector<Tilemap*> tilesVector;
	*/
public:
	SumosChocadoresPlay();
	~SumosChocadoresPlay();
	void Create();
	void Update();
};
#endif
