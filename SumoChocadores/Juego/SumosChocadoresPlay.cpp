#include "stdafx.h"
#include "../EngineMM/Textura.h"
#include "SumosChocadoresPlay.h"
#include "../EngineMM/ImporterAssimp.h"


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
	comCam = new Composite();
	gameInput = new Input();
	reciverMap = gameInput->GetMap();
	intVectorInputUp = &reciverMap["Up"];
	intVectorInputLeft = &reciverMap["Left"];
	intVectorInputRight = &reciverMap["Right"];
	intVectorInputDown = &reciverMap["Down"];
	intVectorInputU = &reciverMap["U"];
	intVectorInputI = &reciverMap["I"];
	camara = new Camera();
	comCam->Add(camara);
	camara->update();

	coso = new Composite();
	cosoMesh = new Mesh();
	cosoMesh->Load3D("Sonic.obj");
	cosoTex = new Textura(L"Sonic.png");
	cosoRender = new MeshRender(cosoTex);
	cosoRender->SetMesh(cosoMesh);
	coso->Add(cosoRender);
	coso->setModelScale(0.5, 0.5, 0.5);
	coso->setVector(D3DXVECTOR3(numx, numy,numz));
	cosoRender->setCamera(camara);

	coso2 = new Composite();
	cosoMesh2 = new Mesh();
	cosoMesh2->Load3D("TracerGun.obj");
	cosoTex2 = new Textura(L"TracerGun.png");
	cosoRender2 = new MeshRender(cosoTex2);
	cosoRender2->SetMesh(cosoMesh2);
	coso2->Add(cosoRender2);
	coso2->setModelScale(1, 1, 1);
	coso2->setVector(D3DXVECTOR3(numy, numx, numz+1));
	cosoRender2->setCamera(camara);

	//coso->Add(coso2);


	/*
	enemigo = new Perseguidor();
	texEnemigo = new Textura(L"Perseguidor.png");
	animacionEnemigo = new Animacion(texEnemigo);
	meshEnemigo = new Mesh();
	animacionEnemigo->SetMesh(meshEnemigo);
	animacionEnemigo->addFrames(2, 2);
	enemigo->Add(animacionEnemigo);
	enemigo->setX(0);
	enemigo->setY(1);
	enemigo->setModelScale(0.1f, 0.1f, 0.1f);
	pj = new Jugador();
	texPj = new Textura(L"PJ.png");
	animacionPj = new Animacion(texPj);
	meshPj = new Mesh();
	animacionPj->SetMesh(meshPj);
	animacionPj->addFrames(2, 2);
	pj->Add(animacionPj);
	pj->setModelScale(0.1f, 0.1f, 0.1f);
	gameover = false;
	vel = 0.0001;
	/*
	sumo = new Composite();
	sumoMesh = new Mesh();
	sumoTex = new Textura(L"PJ.png");
	sumoAnima = new Animacion(sumoTex);
	//sumoRender = new MeshRender(sumoTex);
	sumoAnima->SetMesh(sumoMesh);
	sumoAnima->addFrames(2, 2);
	//sumoRender->SetMesh(sumoMesh);
	sumo->Add(sumoAnima);
	//sumo->Add(sumoRender)
	sumo->setModelScale(1, 1, 1);
	sumo->setVector(D3DXVECTOR3(1, 1, 5));
	*/
	
	/*tiles = new Composite();
	tileMesh = new Mesh();
	tilesMap = new Tilemap(L"grass.jpg",L"Water.jpg",tileMesh);
	tileRender = new MeshRender();
	tiles2 = new Composite();
	tileMesh2 = new Mesh();
	tilesMap2 = new Tilemap(L"rock.png", L"tem.png", tileMesh);
	tileRender2 = new MeshRender();
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
	//coso->setModelRotY(num);
	//coso->setVector(coso->getVector());
	//cosoRender->Blending(1);
	//coso2->setVector(coso2->getVector());
	//cosoRender->Blending(1);
	coso->Render();
	coso2->Render();
	//ImporterAssimp * ImpAss = new ImporterAssimp();
	//ImpAss->usingImporter("TracerGun.obj");
	//ImpAss->usingImporter();

	ImporterAssimp * ImpAss = new ImporterAssimp();
	ImpAss->usingImporter("TracerGun.obj");
	delete ImpAss;
	
	/*
	if (gameover != true)
	{
		if (pj->getX() >= enemigo->getX())
		{
			enemigo->setX(enemigo->getX() + vel);
			enemigo->setVector(D3DXVECTOR3(enemigo->getX(), enemigo->getY(), 1));
		}
		else if (pj->getX() < enemigo->getX())
		{
			enemigo->setX(enemigo->getX() - vel);
			enemigo->setVector(D3DXVECTOR3(enemigo->getX(), enemigo->getY(), 1));
		}
		if (pj->getY() >= enemigo->getY())
		{
			enemigo->setY(enemigo->getY() + vel);
			enemigo->setVector(D3DXVECTOR3(enemigo->getX(), enemigo->getY(), 1));
		}
		else if (pj->getY() < enemigo->getY())
		{
			enemigo->setY(enemigo->getY() - vel);
			enemigo->setVector(D3DXVECTOR3(enemigo->getX(), enemigo->getY(), 1));
		}
		
	}
	
	animacionEnemigo->Blending(2);
	animacionEnemigo->UpdateAn(5);
	enemigo->Render();
	animacionPj->Blending(2);
	animacionPj->UpdateAn(5);
	if (gameover != true)
	{
	*/
		if (gameInput->GetKeyDown(intVectorInputUp))
		{
			numy += 0.01;
		}
		else if (gameInput->GetKeyDown(intVectorInputDown))
		{
			numy -= 0.01;

		}
			if (gameInput->GetKeyDown(intVectorInputLeft))
		{
			numx -= 0.01;
		}
		else if (gameInput->GetKeyDown(intVectorInputRight))
		{
			numx += 0.01;
		}
		if (gameInput->GetKeyDown(intVectorInputU))
		{
			numz -= 0.1;
		}
		else if (gameInput->GetKeyDown(intVectorInputI))
		{
			numz += 0.1;
		}

		coso->setModelPos(numx, numy, numz);
		coso2->setModelPos(numx, numy, numz);

		//coso2->setModelPos(numx+1, numy+1, numz+1);
	
		/*
		if (gameInput->GetKeyDown(intVectorInputUp))
		{
			pj->setY(pj->getY() + vel*2);
			pj->setVector(D3DXVECTOR3(pj->getX(), pj->getY(), 1));
		}
		else if (gameInput->GetKeyDown(intVectorInputDown))
		{
			pj->setY(pj->getY() - vel*2);
			pj->setVector(D3DXVECTOR3(pj->getX(), pj->getY(), 1));
		}
		if (gameInput->GetKeyDown(intVectorInputLeft))
		{
			pj->setX(pj->getX() - vel*2);
			pj->setVector(D3DXVECTOR3(pj->getX(), pj->getY(), 1));
		}
		else if (gameInput->GetKeyDown(intVectorInputRight))
		{
			pj->setX(pj->getX() + vel*2);
			pj->setVector(D3DXVECTOR3(pj->getX(), pj->getY(), 1));
		}
	}
	*/
	//vel += 0.00001;
	//pj->Render();
	
	/*
	if (enemigo->getVector().x < pj->getVector().x + (pj->getScaleV().x / 1) && enemigo->getVector().x >(pj->getVector().x))
	{
		if (enemigo->getVector().y <= pj->getVector().y + (pj->getScaleV().y / 1.2) && enemigo->getVector().y >= (pj->getVector().y))
			gameover = true; 
		else if (enemigo->getVector().y < (pj->getVector().y) && (enemigo->getVector().y + enemigo->getScaleV().y / 1.13) >= pj->getVector().y)
			gameover = true;  
	}

	else if (enemigo->getVector().x <= (pj->getVector().x) && (enemigo->getVector().x + (enemigo->getVector().x / 7)) >= pj->getVector().x)
	{
		if (enemigo->getVector().y <= pj->getVector().y + (pj->getScaleV().y / 1.2) && enemigo->getVector().y >= (pj->getVector().y))
			gameover = true;		
		else if (enemigo->getVector().y <= (pj->getVector().y) && (enemigo->getVector().y + enemigo->getScaleV().y / 1.13) >= pj->getVector().y)
			gameover = true;
	}
	if (gameover)
	{
		pj->setVector(D3DXVECTOR3(-1000, -1000, 0));
		enemigo->setVector(D3DXVECTOR3(1, -1, 1));
		enemigo->setModelScale(2, 2, 2);
	}
	*/
	/*sumo->setVector(sumo->getVector());
	sumoAnima->Blending(2);
	sumoAnima->UpdateAn(2);
	sumo->Render();
	*/
	/*
	for (int i = 0; i < tilesVector.size(); i++) 
	{
		tilesVector[i]->setVector(tilesVector[i]->getVector());
		tilesVector[i]->Render();
	}
	*/
//	tiles->setVector(tiles->getVector());
	//tileRender->Blending(2);

	
}


