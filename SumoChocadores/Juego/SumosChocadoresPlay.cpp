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
	sumoAnima = new Animacion();
	camara = new Camera();
	sumoMesh = new Mesh();
	sumoTex = new Textura(L"Sprite.png");
	sumoRender = new MeshRender(sumoTex);
	sumo = new Composite();
	sumo->Add(sumoRender);
	sumoRender->SetMesh(sumoMesh);
	sumoRender->Blending(2);
	//sumoRender->setModelScale(1, 1, 1);
	//sumoRender->setVector(D3DXVECTOR3(0, 0, 10));
	sumo->setModelScale(1, 1, 1);
	sumo->setVector(D3DXVECTOR3(0, 0, 2));
}

void SumosChocadoresPlay::Update()
{
	camara->update();
	sumo->setVector(sumo->getVector());
	sumo->Render();
}


