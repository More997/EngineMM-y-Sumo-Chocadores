#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/MeshRender.h"
class SumosChocadoresPlay :
	 public ConectorDeEngine
{
private:
	Composite* sumo;
	Mesh* sumoMesh;
	MeshRender* sumoRender;
public:
	SumosChocadoresPlay();
	~SumosChocadoresPlay();
	void Create();
	void Update();
};
#endif
