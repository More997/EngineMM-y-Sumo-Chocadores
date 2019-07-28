#include "stdafx.h"
#include "SceneImporter.h"
#include "MeshRender.h"
#include "Transform.h"

using namespace Assimp;

SceneImporter::SceneImporter()
{
	s = Game::getInstance();
	cout << "Iniciando SceneImporter" << endl;
}
SceneImporter::~SceneImporter()
{
}

void SceneImporter::ImportScene(const string & pFile, Composite * root, Camera * objectCamera)
{
	Importer importer;

	const aiScene* scene = importer.ReadFile(pFile, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	if (!scene)
	{
		cout << "Import failed, we get it next time" << endl;
		return;
	}
	if (!scene->HasMeshes())
	{
		cout << "Not Meshes in this scene" << endl;
	}
	else
	{
		cout << "It has meshes this scene" << endl;
	}
	aiNode * iRoot = scene->mRootNode;
	root->SetName(iRoot->mName.C_Str());
	if (iRoot->mNumChildren <= 0 && iRoot->mNumMeshes <= 0)
		return;
	Transform* rootTransform = new Transform();
	root->Add(rootTransform);
	aiVector3D positionRoot;
	aiQuaternion rotationRoot;
	aiVector3D scaleRoot;
	iRoot->mTransformation.Decompose(scaleRoot, rotationRoot, positionRoot);
	
	rootTransform->SetPos(D3DXVECTOR3(positionRoot.x, positionRoot.y, positionRoot.z));
	rootTransform->SetRot(D3DXVECTOR3(0, 0, 0));
	rootTransform->SetScale(D3DXVECTOR3(scaleRoot.x, scaleRoot.y, scaleRoot.z));
	
	for (unsigned int i = 0; i < iRoot->mNumChildren; i++)
	{
		ImportChildren(iRoot->mChildren[i], root, scene, objectCamera);
	}
}

void SceneImporter::ImportChildren(aiNode * child, Composite * parent, const aiScene * scene, Camera * objectCamera)
{
	aiVector3D position;
	aiQuaternion rotation;
	aiVector3D scale;
	D3DXVECTOR3 rotAxis;
	float angle;

	child->mTransformation.Decompose(scale, rotation, position);
	D3DXQUATERNION auxiliarQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
	D3DXQuaternionToAxisAngle(&auxiliarQuaternion, &rotAxis, &angle);
	D3DXVec3Normalize(&rotAxis, &rotAxis);

	Composite* newComp = new Composite();
	newComp->SetName(child->mName.C_Str());

	cout << "Loading " << newComp->GetName() << " son of " << parent->GetName() << endl;
	Mesh* newMesh = new Mesh();
	Textura* newTex = new Textura();
	MeshRender* newMeshRender = new MeshRender(newMesh, newTex, objectCamera);
	Transform* newTransform = new Transform();

	newComp->Add(newMeshRender);
	
	newComp->Add(newTransform);

	newTransform->SetPos(position.x, position.y, position.z);
	newTransform->SetRot(rotAxis.x*angle, rotAxis.y*angle, rotAxis.z*angle);
	newTransform->SetScale(scale.x, scale.y, scale.z);

	newComp->setModelPos(newTransform->GetPos().x, newTransform->GetPos().y, newTransform->GetPos().z);
	newComp->setModelRotX(newTransform->GetRot().x);
	newComp->setModelRotY(newTransform->GetRot().y);
	newComp->setModelRotZ(newTransform->GetRot().z);
	newComp->setModelScale (newTransform->GetScale().x, newTransform->GetScale().y, newTransform->GetScale().z);
	cout <<"This Object's Position: " << newComp->getVector().x <<","<< newComp->getVector().y << "," << newComp->getVector().z <<endl;
	
	parent->Add(newComp);
	for (unsigned int i = 0; i < child->mNumMeshes; i++)
	{
		const aiMesh* rootModel = scene->mMeshes[child->mMeshes[i]];
		BoundingBox newBB;
		for (unsigned int j = 0; j < rootModel->mNumVertices; j++)
		{
			Vertex newVert;
			newVert.x = rootModel->mVertices[j].x;
			newVert.y = rootModel->mVertices[j].y;
			newVert.z = rootModel->mVertices[j].z;
			newVert.nx = rootModel->mNormals[j].x;
			newVert.ny = rootModel->mNormals[j].y;
			newVert.nz = rootModel->mNormals[j].z;
			newVert.tu = rootModel->mTextureCoords[0][j].x;
			newVert.tv = rootModel->mTextureCoords[0][j].y;


			newBB.xMin = min(rootModel->mVertices[j].x, newBB.xMin);
			newBB.yMin = min(rootModel->mVertices[j].y, newBB.yMin);
			newBB.zMin = min(rootModel->mVertices[j].z, newBB.zMin);
			newBB.xMax = max(rootModel->mVertices[j].x, newBB.xMax);
			newBB.yMax = max(rootModel->mVertices[j].y, newBB.yMax);
			newBB.zMax = max(rootModel->mVertices[j].z, newBB.zMax);

			newMesh->vertexes.push_back(newVert);
		}
		newBB.Refresh();
		newMesh->SetBB(newBB);
		newComp->SetBoundingBox(newMesh->GetBB());
		for (unsigned int k = 0; k < rootModel->mNumFaces; k++)
		{
			const aiFace meshFace = rootModel->mFaces[k];
			for (int l = 0; l < 3; l++)
				newMesh->indexes.push_back(meshFace.mIndices[l]);
		}
		LPDIRECT3DINDEXBUFFER9 ib;
		LPDIRECT3DVERTEXBUFFER9 vb;
		s->getDev()->CreateVertexBuffer(newMesh->vertexes.size() * sizeof(Vertex), 0, CUSTOMFVF, D3DPOOL_MANAGED, &vb, NULL);
		s->getDev()->CreateIndexBuffer(newMesh->indexes.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, NULL);

		VOID* lockedData = NULL;
		vb->Lock(0, 0, (void**)&lockedData, 0); //vb me da null?
		memcpy(lockedData, newMesh->vertexes.data(), newMesh->vertexes.size() * sizeof(Vertex));
		vb->Unlock();

		ib->Lock(0, 0, (void**)&lockedData, 0);
		memcpy(lockedData, newMesh->indexes.data(), newMesh->indexes.size() * sizeof(WORD));
		ib->Unlock();

		s->getDev()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		newMesh->setInd(ib);
		newMesh->setVB(vb);
	}
	
		if (child->mNumChildren > 0)
		{
			for (unsigned int i = 0; i < child->mNumChildren; i++)
			{
				ImportChildren(child->mChildren[i], newComp, scene, objectCamera);
			}
		}
		
	}

