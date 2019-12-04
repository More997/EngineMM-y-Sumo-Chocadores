#include "stdafx.h"
#include "GameMMPlay.h"

GameMMPlay::GameMMPlay()
{
}
GameMMPlay::~GameMMPlay()
{
}
void GameMMPlay::SetRoot(Composite* _root)
{
	root = _root;
}
void GameMMPlay::LoadContent()
{	
	cameraView = new Camera();
	

	game = Game::getInstance();

	
	D3DXCreateEffectFromFile(
		game->GetDevice(), L"EffectDamage.fx", NULL, NULL,
		D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
		NULL, &shaderEffect, NULL);


	gameInput = new Input();
	reciverMap = gameInput->GetMap();
	intVectorInputUp = &reciverMap["MoveUp"];
	intVectorInputLeft = &reciverMap["MoveLeft"];
	intVectorInputRight = &reciverMap["MoveRight"];
	intVectorInputDown = &reciverMap["MoveDown"];
	intVectorInputSpace = &reciverMap["RotateLeft"];
	//float numX = 0;
	//float numY = 0;
	/*
	paulMesher = new Mesher();
	paulMesher->Load3D("TestCube.obj");
	paul = new Composite();
	paulTexture = new Texture(L"sonic2.png");
	paulAnimation = new Animated(paulTexture, cameraView);
	paulAnimation->SetMesher(paulMesher);
	paul->Add(paulAnimation);
	paul->SetVectorPosition(D3DXVECTOR3(-0, -0.5, 1));
	paul->Add(paulAnimation);
	paulXPositionToSet = 6;
	//WORD indexes[] = { 3,0,1,3,1,2 };
	paulAnimation->AddFrameAnimation(4, 1);
	paulAnimation->Blending(2);
	*/

	Vertex tileSetVertexes[] =
	{
		{ -0.6f,  0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.6f,  0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f },
		{ 0.6f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
		{ -0.6f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f }
	};
	WORD tileSetIndexes[] = { 0, 1, 2, 2, 3, 0 };

	tileSet = new TileSet(tileSetVertexes, tileSetIndexes, 2, 19);
	int greenHillTiles = 8;
	int emptyTiles1 = 4;
	int emptyTiles2 = 15;
	int brownHillTiles = 8;
	int brownHillTiles2 = 7;

	for (int i = 0; i < brownHillTiles; i++)
	{
		tileSet->AddPalette(L"GreenHillTileNoGrass.png");
	}
	for (int i = 0; i < emptyTiles1; i++)
	{
		tileSet->AddPalette(L"Spikes.png");
	}
	for (int i = 0; i < brownHillTiles2; i++)
	{
		tileSet->AddPalette(L"GreenHillTileNoGrass.png");
	}
	for (int i = 0; i < brownHillTiles; i++)
	{
		tileSet->AddPalette(L"GreenHillTile.png");
	}
	for (int i = 0; i < emptyTiles1; i++)
	{
		tileSet->AddPalette(L"EmptyTile.png");
	}
	for (int i = 0; i < brownHillTiles2; i++)
	{
		tileSet->AddPalette(L"GreenHillTile.png");
	}

	boxForTiler = new BoundingBox();
	tileSet->SetBoundingBox(*boxForTiler);
	tileRenderer = new TileRenderer(cameraView);
	tileRenderer->SetTiler(*tileSet);
	tileRenderer->SetBoundingBox(*tileSet->GetBoundingBox());
	tileRenderer->SetHasMesh(false);
	//tilerenderer->SetCamara(*cameraView);
	//3D

	bondi = new Composite();
	bondiMesher = new Mesher();
	//bondiMesher->Load3D("almeja.obj");
	//bondiTexture = new Texture(L"almeja.jpg");
	bondiMesher->Load3D("TracerGun.obj");
	bondiTexture = new Texture(L"TracerGun.png");
	
	//bondiTexture->SetBlend(3);
	//bondiRenderer->Blending(3);
	
	//bondiTexture->SetFiltro(1);
	//bondiTexture->SetWrap(1);
	
	//bondiMesher->Load3D("bondi.obj");
	//bondiTexture = new Texture(L"sonic2.png");
	bondi->SetBoundingBox(bondiMesher->GetBoundingBox());
	bondiRenderer = new MeshRenderer(bondiTexture, cameraView);
	bondiRenderer->SetMesher(bondiMesher);
	bondi->test = true;
	bondi->Add(bondiRenderer);
	bondi->SetModelPosition(0, 0, 0);
	bondi->SetModelScale(4, 4, 4);
	
	bsp = new BSP();

	SceneImporter sI;
	
	importer = new SceneImporter();
	root = new Composite();
	importer->ImportScene("bsptest4.obj", root, cameraView/*, dev*/);
	//bsp->AddPlaneOrObject(root);
	//root->SetModelPosition(10, 0, 10);
	//root->SetModelScale(1, 1, 1);
	playerCube = root->FindChild("Cube");
	cameraView->Move(D3DXVECTOR3(-0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
	//numX = -8.4;
	numZ = -25;
	extraNum = -25;
}
void GameMMPlay::FrameEvent()
{
		cameraView->Update();
		cameraView->Move(D3DXVECTOR3(numX, 5.7, numZ), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		cameraView->Render();
		
		D3DXHANDLE handling = shaderEffect->GetTechniqueByName("RedColor");
		shaderEffect->SetTechnique(handling);
		passesNumber = 2;
		UINT passes = passesNumber;
		D3DXMATRIX MVP = bondi->GetTransformationMatrix() * cameraView->GetViewMatrix() * cameraView->GetProjection();
		D3DXMATRIX rotationMatrix = bondi->GetRotationMatrix();
		shaderEffect->SetMatrix("MVPMatrix", &MVP);
		shaderEffect->SetMatrix("rotMatrix", &rotationMatrix);
		shaderEffect->SetVector("lightDirection", &D3DXVECTOR4(1, 1, 1, 0));
		shaderEffect->SetVector("lightColor", &D3DXVECTOR4(4, 1, 5, 0));
		shaderEffect->SetVector("ambientColor", &D3DXVECTOR4(0.3f, 0, 0, 0));
		shaderEffect->Begin(&passes, 0);
		for (UINT pass = 0; pass < passes; pass++)
		{
			shaderEffect->BeginPass(pass);
			game->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
			shaderEffect->EndPass();
		}
		bondi->Render();
		shaderEffect->End();
		
		



		/*
		paul->SetVectorPosition(D3DXVECTOR3(paulXPositionToSet, -1, 5));
		paul->SetModelScale(4, 2, 1);
		paulAnimation->UpdateAnimation(0.25);
		*/
		//cout << paul->GetPosition().z << endl;
		//for que actualiza camaras


		//Recorrer root y renderizar cada parte.
		
		
		
		//3D
		
		//forTesting = bondi->GetBoundingBox();
	
		if (gameInput->GetKeyDown(intVectorInputUp))
			numZ += 0.5;
		else if (gameInput->GetKeyDown(intVectorInputDown))
		{
			numZ -= 0.5;
			cout << "MOVIENDO CAMARA HACIA ATRAS";
		}
		if (gameInput->GetKeyDown(intVectorInputLeft))
			numX -= 0.5;
		else if (gameInput->GetKeyDown(intVectorInputRight))
			numX += 0.5;
		if (gameInput->GetKeyDown(intVectorInputSpace))
			extraNum += 0.5;

		playerCube->SetModelPosition(numX, numY, 20);

		//else
			//numZ -= 0.5;
		
		
		//std::cout << numZ << " ";
		//numZ = 1;
		// std::cout << "Modelo sin assimp en posicion " << numZ << " en Z" << std::endl;
		bondi->SetModelRotation(0, extraNum, extraNum);
		//numZ -= 0.05;
		/*
		tileRenderer->SetModelPosition(-0, 0, 0);
		tileRenderer->SetModelScale(0, 0, 0);
		*/
		
		//paulXPositionToSet -= 0.01;
		
		//playerCube->SetModelPosition(0, 0, 0);
		//root->Update();

		//bsp->CheckTree(cameraView, root); // Comprueba si los objetos estan entre los planos*/

		/*
		list<Composite*> objectsToDraw = bsp->GetObjectsToDraw();

		for (unsigned int i = 0; i < bsp->planos.size(); i++)
		{
			float testing = bsp->planos.at(i)->GetPosition().x;

			bsp->planos.at(i)->Render();
		}

		for (std::list<Composite*>::iterator i = objectsToDraw.begin(); i != objectsToDraw.end(); i++)
		{
			(*i)->Render();
		}
		*/
		//bondi->Render(); //!!!!!
		//root->Render();
		//tileRenderer->Render();
		//paul->Render();
}