#include "stdafx.h"
#include "../EngineMM/Textura.h"
#include "SumosChocadoresPlay.h"


SumosChocadoresPlay::SumosChocadoresPlay()
{
}


SumosChocadoresPlay::~SumosChocadoresPlay()
{
}

void SumosChocadoresPlay::Create()
{
	camara = new Camera();

	sumoMesh = new Mesh();
	sumoTex = new Textura(L"yaya.jpg");
	sumoRender = new MeshRender(sumoTex);
	sumo = new Composite();
	sumo->Add(sumoRender);
	sumoRender->SetMesh(sumoMesh);
	sumoRender->Blending(1);
	//sumoRender->setModelScale(1, 1, 1);
	//sumoRender->setVector(D3DXVECTOR3(0, 0, 10));
	sumo->setModelScale(1, 1, 1);
	sumo->setVector(D3DXVECTOR3(0, 0, 5));
}

void SumosChocadoresPlay::Update()
{
	camara->update();
	sumo->setVector(sumo->getVector());
	sumo->Render();
}


