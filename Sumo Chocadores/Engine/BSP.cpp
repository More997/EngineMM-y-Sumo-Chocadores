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
			if (child->GetName().find("Individual") != string::npos)
			{
				cout << "Loading Object " << child->GetName() << endl;
				AddBSP_Object(child);
				AddPlaneOrObject(child);
			}
			else if (child->GetName().find(bspPlaneDefault) != string::npos)
			{
				cout << "Loading Plane " << child->GetName() << endl;
				planos.push_back(child);
				LoadPlane(child);
				AddPlaneOrObject(child);

			}
		}
	}
}

void BSP::CheckTree(Transform* cameraTrans, Composite* root)
{
	objectsToDraw.clear();
	for (unsigned int i = 0; i < BSPplanes.size(); i++)
	{
		std::list<Composite*>::iterator it = allObjects.begin();

		while (it != allObjects.end())
		{
			bool fullBoxIn = false;
			BoundingBox fullAuxBB = (*it)->getTransBB();

			D3DXVECTOR3 vertexesFull[8];

			vertexesFull[0] = D3DXVECTOR3(fullAuxBB.xMax, fullAuxBB.yMax, fullAuxBB.zMax);
			vertexesFull[1] = D3DXVECTOR3(fullAuxBB.xMax, fullAuxBB.yMax, fullAuxBB.zMin);
			vertexesFull[2] = D3DXVECTOR3(fullAuxBB.xMin, fullAuxBB.yMax, fullAuxBB.zMax);
			vertexesFull[3] = D3DXVECTOR3(fullAuxBB.xMin, fullAuxBB.yMax, fullAuxBB.zMin);
			vertexesFull[4] = D3DXVECTOR3(fullAuxBB.xMax, fullAuxBB.yMin, fullAuxBB.zMax);
			vertexesFull[5] = D3DXVECTOR3(fullAuxBB.xMax, fullAuxBB.yMin, fullAuxBB.zMin);
			vertexesFull[6] = D3DXVECTOR3(fullAuxBB.xMin, fullAuxBB.yMin, fullAuxBB.zMax);
			vertexesFull[7] = D3DXVECTOR3(fullAuxBB.xMin, fullAuxBB.yMin, fullAuxBB.zMin);

			float camDotCoord = D3DXPlaneDotCoord(BSPplanes.at(i), &cameraTrans->GetPos());


			for (unsigned int j = 0; j < 8; j++)
			{
				float vertexDotCoord = D3DXPlaneDotCoord(BSPplanes.at(i), &vertexesFull[j]);

				if ((camDotCoord > 0 && vertexDotCoord > 0) || (camDotCoord < 0 && vertexDotCoord < 0))
				{
					fullBoxIn = true;
				}
			}
			if (fullBoxIn)
			{
				CheckObj(*it, cameraTrans);
			}	
			it++;

		}
	}

}

void BSP::CheckObj(Composite* object, Transform* cameraTrans)
{
				bool draw = false;
				D3DXVECTOR3 vertexes[8];
				BoundingBox ObjBB = object->GetTransBBNoParenting();

				vertexes[0] = D3DXVECTOR3(ObjBB.xMax, ObjBB.yMax, ObjBB.zMax);
				vertexes[1] = D3DXVECTOR3(ObjBB.xMax, ObjBB.yMax, ObjBB.zMin);
				vertexes[2] = D3DXVECTOR3(ObjBB.xMin, ObjBB.yMax, ObjBB.zMax);
				vertexes[3] = D3DXVECTOR3(ObjBB.xMin, ObjBB.yMax, ObjBB.zMin);
				vertexes[4] = D3DXVECTOR3(ObjBB.xMax, ObjBB.yMin, ObjBB.zMax);
				vertexes[5] = D3DXVECTOR3(ObjBB.xMax, ObjBB.yMin, ObjBB.zMin);
				vertexes[6] = D3DXVECTOR3(ObjBB.xMin, ObjBB.yMin, ObjBB.zMax);
				vertexes[7] = D3DXVECTOR3(ObjBB.xMin, ObjBB.yMin, ObjBB.zMin);

				for (unsigned int j = 0; j < 8 && !draw; j++)
				{
					_InsideThePlanes = 0;
					for (unsigned int l = 0; l < BSPplanes.size(); l++)
					{
						float camDotCoord = D3DXPlaneDotCoord(BSPplanes.at(l), &cameraTrans->GetPos());
						float vertexDotCoord = D3DXPlaneDotCoord(BSPplanes.at(l), &vertexes[j]);


						if ((camDotCoord > 0 && vertexDotCoord > 0) || (camDotCoord < 0 && vertexDotCoord < 0) || ((camDotCoord == 0 && vertexDotCoord == 0)))
						{							
							_InsideThePlanes++;
							if (_InsideThePlanes >= BSPplanes.size())
								draw = true;
						}
					}
				}
				if (draw)
				{
					objectsToDraw.push_back(object);
				}
				for (int i = 0; i < (object)->GetComponents().size(); i++)
				{
					Composite * child = dynamic_cast<Composite*>((object)->GetComponents()[i]);
					if (child != nullptr)
					{
						if (child->GetName().find("Child") != string::npos)
						{
							CheckObj(child, cameraTrans);
						}
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