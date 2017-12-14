#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
#include "../EngineMM/Camera.h"
#include "../EngineMM/Tilemap.h"
#include "../EngineMM/MeshRender.h"
#include "Perseguidor.h"
class SumosChocadoresPlay :
	 public ConectorDeEngine
{
private:
	Camera* camara;
	float num = 0;
	float num2 = 0;
	Mesh* cosoMesh;
	Textura* cosoTex;
	MeshRender* cosoRender;
	Composite*coso;
	BoundingBox bbtest;
	Perseguidor* enemigo;
	
public:
	SumosChocadoresPlay();
	~SumosChocadoresPlay();
	void Create();
	void Update();
};
#endif
