#include "stdafx.h"
#include "BSP.h"
#include "MeshRenderer.h"


void BSP::AddPlaneOrObject(Composite * root)
{
	string bspPlaneDefault = "BSP_Plane";

	for (int i = 0; i < root->GetComponents().size(); i++)
	{
		Composite * child = dynamic_cast<Composite*>(root->GetComponents()[i]);
		if (child != nullptr)
		{
			string objectName = child->GetName();
			size_t found = objectName.find(bspPlaneDefault);
			if (child->GetName().find("Individual") != string::npos || child->GetName().find(bspPlaneDefault) != string::npos) 
			{
				if (found != string::npos)
				{
					cout << "Plane Load: " << child->GetName() << endl;
					planos.push_back(child);
					LoadPlane(child);
				}
				else
				{
					cout << "Object Load: " << child->GetName() << endl;
					AddBSP_Object(child);
				}

			AddPlaneOrObject(child);
			}
		}
	}
}

void BSP::CheckTree(Transform* cameraTrans, Composite* root)
{
	objectsToDraw = allObjects;

	for (unsigned int i = 0; i < BSPplanes.size(); i++)
	{
		std::list<Composite*>::iterator it = objectsToDraw.begin();

		while (it != objectsToDraw.end())
		{
			BoundingBox auxBB = (*it)->GetTransBBNoParenting();

			D3DXVECTOR3 vertexes[8];

			vertexes[0] = D3DXVECTOR3(auxBB.xMax, auxBB.yMax, auxBB.zMax);
			vertexes[1] = D3DXVECTOR3(auxBB.xMax, auxBB.yMax, auxBB.zMin);
			vertexes[2] = D3DXVECTOR3(auxBB.xMin, auxBB.yMax, auxBB.zMax);
			vertexes[3] = D3DXVECTOR3(auxBB.xMin, auxBB.yMax, auxBB.zMin);
			vertexes[4] = D3DXVECTOR3(auxBB.xMax, auxBB.yMin, auxBB.zMax);
			vertexes[5] = D3DXVECTOR3(auxBB.xMax, auxBB.yMin, auxBB.zMin);
			vertexes[6] = D3DXVECTOR3(auxBB.xMin, auxBB.yMin, auxBB.zMax);
			vertexes[7] = D3DXVECTOR3(auxBB.xMin, auxBB.yMin, auxBB.zMin);

			float camDotCoord = D3DXPlaneDotCoord(BSPplanes.at(i), &cameraTrans->GetPos());

			bool draw = false;

			for (unsigned int j = 0; j < 8 && !draw; j++)
			{
				float vertexDotCoord = D3DXPlaneDotCoord(BSPplanes.at(i), &vertexes[j]);

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

void BSP::LoadPlane(Composite* plane)
{
	D3DXVECTOR3 vertices[3];
	MeshRenderer* meshRenderer = plane->GetComponent<MeshRenderer>();
	for (unsigned int i = 0; i < 3; i++)
	{
		vertices[i] = D3DXVECTOR3(
			meshRenderer->m_Model->vertexes.at(i).x,
			meshRenderer->m_Model->vertexes.at(i).y,
			meshRenderer->m_Model->vertexes.at(i).z);
	}


	Transform* transform = plane->GetComponent<Transform>();
	D3DXPLANE* newPlane = new D3DXPLANE();
	D3DXPlaneFromPoints(newPlane, &vertices[0], &vertices[1], &vertices[2]);
	D3DXPlaneNormalize(newPlane, newPlane);

	D3DXMATRIX matrix;
	D3DXMATRIX transMat;
	D3DXMATRIX rotXMat;
	D3DXMATRIX rotYMat;
	D3DXMATRIX rotZMat;
	D3DXMatrixTranslation(&transMat, transform->GetPos().x, transform->GetPos().y, transform->GetPos().z);
	D3DXMatrixRotationX(&rotXMat, transform->GetRot().x);
	D3DXMatrixRotationY(&rotYMat, transform->GetRot().y);
	D3DXMatrixRotationZ(&rotZMat, transform->GetRot().z);

	matrix = rotXMat * rotYMat * rotZMat * transMat;

	D3DXMatrixInverse(&matrix, NULL, &matrix);
	D3DXMatrixTranspose(&matrix, &matrix);
	D3DXPlaneTransform(newPlane, newPlane, &matrix);

	BSPplanes.push_back(newPlane);
}

void BSP::AddBSP_Object(Composite * object)
{
	allObjects.push_back(object);
}

list<Composite*> BSP::GetObjectsToDraw()
{
	return objectsToDraw;
}

void BSP::ResetPlanes()
{
	BSPplanes.clear();
}