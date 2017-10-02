#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
#include "../EngineMM/Camera.h"
class SumosChocadoresPlay :
	 public ConectorDeEngine
{
private:
	Animacion * sumoAnima;
	Composite* sumo;
	Mesh* sumoMesh;
	MeshRender* sumoRender;
	Textura* sumoTex;
	Camera* camara;
public:
	SumosChocadoresPlay();
	~SumosChocadoresPlay();
	void Create();
	void Update();
};
#endif
