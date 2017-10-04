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
	tiles = new Composite();
	tileMesh = new Mesh();
	tilesMap = new Tilemap(L"grass.jpg",L"Water.jpg",tileMesh);
	sumo->Add(sumoRender);
	sumoRender->SetMesh(sumoMesh);
	sumoRender->Blending(2);
	tiles->Add(tilesMap);
	tiles->setVector(D3DXVECTOR3(-2, 15, 10));
	sumo->setModelScale(1, 1, 1);
	sumo->setVector(D3DXVECTOR3(0, 0, 2));
}

void SumosChocadoresPlay::Update()
{
	camara->update();
	sumo->setVector(sumo->getVector());
	sumo->Render();
	tiles->setVector(tiles->getVector());
	tiles->Render();
}


