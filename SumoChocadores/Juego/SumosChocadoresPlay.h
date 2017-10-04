#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
#include "../EngineMM/Camera.h"
#include "../EngineMM/Tilemap.h"
class SumosChocadoresPlay :
	 public ConectorDeEngine
{
private:
	Animacion * sumoAnima;
	Composite* sumo;
	Mesh* sumoMesh;
	MeshRender* sumoRender;
	Textura* sumoTex;
	Composite* tiles;
	Tilemap*  tilesMap;
	Mesh* tileMesh;
	Camera* camara;
public:
	SumosChocadoresPlay();
	~SumosChocadoresPlay();
	void Create();
	void Update();
};
#endif
