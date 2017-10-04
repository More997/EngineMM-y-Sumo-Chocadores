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
	coso = new Composite();
	camara = new Camera();
	cosoMesh = new Mesh();
	cosoMesh->Load3D("Model.obj");
	cosoTex = new Textura(L"Pickups_lambert1_Normal.png");
	cosoRender = new MeshRender(cosoTex);
	cosoRender->SetMesh(cosoMesh);
	coso->Add(cosoRender);
	/*sumoAnima = new Animacion();
	
	sumoMesh = new Mesh();
	sumoTex = new Textura(L"Sprite.png");
	sumoRender = new MeshRender(sumoTex);
	sumo = new Composite();
	tiles = new Composite();
	tileMesh = new Mesh();
	tilesMap = new Tilemap(L"grass.jpg",L"Water.jpg",tileMesh);
	tileRender = new MeshRender();
	tiles2 = new Composite();
	tileMesh2 = new Mesh();
	tilesMap2 = new Tilemap(L"tem.png", L"tem.png", tileMesh);
	tileRender2 = new MeshRender();
	sumo->Add(sumoRender);
	sumoRender->SetMesh(sumoMesh);
	tiles->Add(tilesMap);
	tileRender->SetMesh(tileMesh);
	tiles->setVector(D3DXVECTOR3(-2, 15, 10));
	sumo->setModelScale(1, 1, 1);
	sumo->setVector(D3DXVECTOR3(0, 0, 2));
	tilesVector.push_back(tilesMap);
	tilesVector.push_back(tilesMap2);*/
}

void SumosChocadoresPlay::Update()
{
	camara->update();
	coso->setVector(coso->getVector()+(1,0,0));

	/*
	sumo->setVector(sumo->getVector());
	sumoRender->Blending(2);
	sumo->Render();
	for (int i = 0; i < tilesVector.size(); i++) 
	{
		tilesVector[i]->setVector(tilesVector[i]->getVector());

		tilesVector[i]->Render();
	}
	/*tiles->setVector(tiles->getVector());
	tileRender->Blending(0);
	tiles->Render();*/
	
}


