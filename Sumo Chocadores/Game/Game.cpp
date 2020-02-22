#include "stdafx.h"
#include "Game.h"

#include "Model.h"
#include "Composite.h"
#include "Transform.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Frustrum.h"
#include "SceneImporter.h"

#include <iostream>

Composite* item;

void Game::LoadContent(LPDIRECT3DDEVICE9 dev)
{
	//Inputs
	m_Input->inputMap["Left"] = new vector<int>{ DIK_LEFTARROW };
	m_Input->inputMap["Right"] = new vector<int>{ DIK_RIGHTARROW };
	m_Input->inputMap["Up"] = new vector<int>{ DIK_UPARROW };
	m_Input->inputMap["Down"] = new vector<int>{ DIK_DOWNARROW };

	m_Input->inputMap["WASDLeft"] = new vector<int>{ DIK_A };
	m_Input->inputMap["WASDRight"] = new vector<int>{ DIK_D };
	m_Input->inputMap["WASDUp"] = new vector<int>{ DIK_W };
	m_Input->inputMap["WASDDown"] = new vector<int>{ DIK_S };

	m_Input->inputMap["E"] = new vector<int>{ DIK_E };
	m_Input->inputMap["Q"] = new vector<int>{ DIK_Q };

	camera->isometricView = false;
	
	SceneImporter sI;

	sI.Import("bspTest16.dae", root, dev);

	bsp->AddPlaneOrObject(root);

	item = root->findChild("Individual Cube_001");

	camera->m_Transform->SetPos(D3DXVECTOR3(0, 1, -10));
	camera->View(dev, 60, 640, 480, 0.1f, 30);
	dev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

}
void Game::Update(LPDIRECT3DDEVICE9 dev)
{
	if (m_Input->GetKey("Left"))
		item->GetComponent<Transform>()->Move(-item->GetComponent<Transform>()->GetRight() * 0.1f);

	if (m_Input->GetKey("Right"))
		item->GetComponent<Transform>()->Move(item->GetComponent<Transform>()->GetRight() * 0.1f);

	if (m_Input->GetKey("Up"))
		item->GetComponent<Transform>()->Move(item->GetComponent<Transform>()->GetForward() * 0.1f);

	if (m_Input->GetKey("Down"))
		item->GetComponent<Transform>()->Move(-item->GetComponent<Transform>()->GetForward() * 0.1f);



	if (m_Input->GetKey("WASDLeft"))
	{
		camera->m_Transform->Move(-camera->m_Transform->GetRight() * 0.1f);
		camera->View(dev, 60, 640, 480, 0.1f, 30);
	}

	if (m_Input->GetKey("WASDRight"))
	{
		camera->m_Transform->Move(camera->m_Transform->GetRight() * 0.1f);
		camera->View(dev, 60, 640, 480, 0.1f, 30);
	}

	if (m_Input->GetKey("WASDUp"))
	{
		camera->m_Transform->Move(D3DXVECTOR3(0, 0, 0.1f));
		camera->View(dev, 60, 640, 480, 0.1f, 30);
	}

	if (m_Input->GetKey("WASDDown"))
	{
		camera->m_Transform->Move(D3DXVECTOR3(0, 0, -0.1f));
		camera->View(dev, 60, 640, 480, 0.1f, 30);
	}

	if (m_Input->GetKey("E"))
	{
		
	}
	frustum->UpdatePlanes(camera->viewMatrix * camera->projMatrix);

}
Game::~Game()
{
}
