#include "stdafx.h"
#include "../EngineMM/Textura.h"
#include "SumosChocadoresPlay.h"


SumosChocadoresPlay::SumosChocadoresPlay()
{
}


SumosChocadoresPlay::~SumosChocadoresPlay()
{
	/*
	delete sumoMesh;
	delete sumoTex;
	delete sumoAnima;
	delete sumo;
	delete tiles;
	delete tileMesh;
	delete tilesMap;
	delete tileRender;
	delete tiles2;
	delete tileMesh2;
	delete tilesMap2;
	delete tileRender2;
	*/
}

void SumosChocadoresPlay::Create()
{
	camara = new Camera();
	
	coso = new Composite();
	cosoMesh = new Mesh();
	cosoMesh->Load3D("model.obj");
	//cosoTex = new Textura(L"TracerGun.png");
	cosoRender = new MeshRender(/*cosoTex*/);
	cosoRender->SetMesh(cosoMesh);
	coso->Add(cosoRender);
	coso->setModelScale(10, 10, 10);
	coso->setVector(D3DXVECTOR3(0, 0, 10));
	
	/*
	sumoMesh = new Mesh();
	sumoTex = new Textura(L"walk.png");
	sumoAnima = new Animacion(sumoTex);
	sumo = new Composite();
	tiles = new Composite();
	tileMesh = new Mesh();
	tilesMap = new Tilemap(L"grass.jpg",L"Water.jpg",tileMesh);
	tileRender = new MeshRender();
	tiles2 = new Composite();
	tileMesh2 = new Mesh();
	tilesMap2 = new Tilemap(L"perfil.jpg", L"tem.png", tileMesh);
	tileRender2 = new MeshRender();
	//sumo->Add(sumoRender);
	sumoAnima->SetMesh(sumoMesh);
	sumo->setModelScale(1, 1, 1);
	sumo->setVector(D3DXVECTOR3(0, 0, 2));
	sumo->Add(sumoAnima);
	sumoAnima->addFrames(6, 5);
	tiles->Add(tilesMap);
	tileRender->SetMesh(tileMesh);
	tiles->setVector(D3DXVECTOR3(-2, 15, 10));
	tilesVector.push_back(tilesMap);
	tilesVector.push_back(tilesMap2);
	*/
}

void SumosChocadoresPlay::Update()
{
	camara->update();
	coso->setModelRotX(+1);
	coso->setVector(coso->getVector());
	coso->Render();
	/*
	sumo->setVector(sumo->getVector());
	sumoAnima->Blending(2);
	sumo->Render();
	for (int i = 0; i < tilesVector.size(); i++) 
	{
		tilesVector[i]->setVector(tilesVector[i]->getVector());
		tilesVector[i]->Render();
	}
	tiles->setVector(tiles->getVector());
	tileRender->Blending(1);
	tiles->Render();
	sumoAnima->UpdateAn(1);
	*/
}


