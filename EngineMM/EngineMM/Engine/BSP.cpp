#include "stdafx.h"
#include "BSP.h"
#include <D3dx9math.h>
BSP::BSP()
{
}
void BSP::AddPlaneOrObject(Composite * root)
{
	string BSPPlaneDefault = "BSP_Plane";

	for (int i = 0; i < root->GetComponents().size(); i++)
	{
		Composite * child = dynamic_cast<Composite*>(root->GetComponents()[i]);
		if (child != nullptr)
		{
			string objectName = child->GetName();
			size_t found = objectName.find(BSPPlaneDefault);
			if (found != string::npos)
			{
				cout << "BSP: Cargando plano " << child->GetName() << ". Posicion en Z == " << child->GetPosition().z << endl;
				planos.push_back(child);
				LoadPlane(child);
			}
			else
			{
				//if(child->GetName() != "")
				{
					cout << "Cargando objeto " << child->GetName() << ". Posicion en Z == " << child->GetPosition().z << endl;
					
					AddBSPObject(child);
				}
			}

			AddPlaneOrObject(child);
		}
	}
}

void BSP::CheckTree(Composite* cameraPosition, Composite * root)
{
	objectsToDraw = allObjects;

	for (unsigned int i = 0; i < BSPPlanes.size(); i++)
	{
		std::list<Composite*>::iterator it = objectsToDraw.begin();
		while (it != objectsToDraw.end())
		{
			BoundingBox auxBB = (*it)->GetBoundingBox();
			D3DXVECTOR3 vertexes[8];

			vertexes[0] = D3DXVECTOR3(auxBB.xMax, auxBB.yMax, auxBB.zMax);
			vertexes[1] = D3DXVECTOR3(auxBB.xMax, auxBB.yMax, auxBB.zMin);
			vertexes[2] = D3DXVECTOR3(auxBB.xMin, auxBB.yMax, auxBB.zMax);
			vertexes[3] = D3DXVECTOR3(auxBB.xMin, auxBB.yMax, auxBB.zMin);
			vertexes[4] = D3DXVECTOR3(auxBB.xMax, auxBB.yMin, auxBB.zMax);
			vertexes[5] = D3DXVECTOR3(auxBB.xMax, auxBB.yMin, auxBB.zMin);
			vertexes[6] = D3DXVECTOR3(auxBB.xMin, auxBB.yMin, auxBB.zMax);
			vertexes[7] = D3DXVECTOR3(auxBB.xMin, auxBB.yMin, auxBB.zMin);

			float camDotCoord = D3DXPlaneDotCoord(BSPPlanes.at(i), &cameraPosition->GetPosition());
			bool draw = false;
			
			for (unsigned int j = 0; j < 8 && !draw; j++)
			{
				float vertexDotCoord = D3DXPlaneDotCoord(BSPPlanes.at(i), &vertexes[j]);
				if ((camDotCoord > 0 && vertexDotCoord > 0) || (camDotCoord < 0 && vertexDotCoord < 0))
					draw = true;
			}
		if (!draw)
				objectsToDraw.erase(it++);
		else
			it++;
		}
	}
}
void BSP::LoadPlane(Composite * plane)
{
	D3DXVECTOR3 vertices[3];
	MeshRenderer* meshRenderer = plane->GetComponent<MeshRenderer>();
	for (unsigned int i = 0; i < 3; i++)
	{
		vertices[i] = D3DXVECTOR3(
			meshRenderer->theMesher->vertexes.at(i).x,
			meshRenderer->theMesher->vertexes.at(i).y,
			meshRenderer->theMesher->vertexes.at(i).z);
	}
	D3DXPLANE* newPlane = new D3DXPLANE();
	D3DXPlaneFromPoints(newPlane, &vertices[0], &vertices[1], &vertices[2]);
	D3DXPlaneNormalize(newPlane, newPlane);
	D3DXMATRIX matrix;
	D3DXMATRIX transMat;
	D3DXMATRIX rotXMat;
	D3DXMATRIX rotYMat;
	D3DXMATRIX rotZMat;
	D3DXMatrixTranslation(&transMat, plane->GetPosition().x, plane->GetPosition().y, plane->GetPosition().z);
	D3DXMatrixRotationX(&rotXMat, plane->GetRotation().x);
	D3DXMatrixRotationY(&rotYMat, plane->GetRotation().y);
	D3DXMatrixRotationZ(&rotZMat, plane->GetRotation().z);

	matrix = rotXMat * rotYMat * rotZMat * transMat;

	D3DXMatrixInverse(&matrix, NULL, &matrix);
	D3DXMatrixTranspose(&matrix, &matrix);
	D3DXPlaneTransform(newPlane, newPlane, &matrix);

	BSPPlanes.push_back(newPlane);
}
void BSP::AddBSPObject(Composite * object)
{
	allObjects.push_back(object);
}

list<Composite*> BSP::GetObjectsToDraw()
{
	return objectsToDraw;
}
void BSP::ResetPlanes()
{
	BSPPlanes.clear();
}