#include "stdafx.h"
#include "SumosChocadoresPlay.h"


SumosChocadoresPlay::SumosChocadoresPlay()
{
}


SumosChocadoresPlay::~SumosChocadoresPlay()
{
}

void SumosChocadoresPlay::Create()
{
	sumo = new Composite();
	sumoMesh = new Mesh();
	sumoRender = new MeshRender();
	sumoRender->SetMesh(sumoMesh);
	sumo->Add(sumoRender);
	sumo->setVector(D3DXVECTOR3(-1, 0, 10));
}

void SumosChocadoresPlay::Update()
{
	sumo->getVector();
	sumoRender->Render();
}


