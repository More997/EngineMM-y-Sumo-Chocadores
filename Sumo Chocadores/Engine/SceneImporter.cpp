#include "stdafx.h"
#include "SceneImporter.h"
#include "Transform.h"
#include "Model.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "BoundingBox.h"
#include <assert.h>

using namespace Assimp;

void SceneImporter::Import(const std::string& filename, Composite* root, LPDIRECT3DDEVICE9 dev)
{
	Importer importer;

	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene)
	{
		cout << "ERROR: Scene didn't load" << endl;
		return;
	}
	else
		cout << "Scene loaded" << endl;

	if (!scene->HasMeshes())
	{
		cout << "The Scene doesn't have meshes" << endl;
		return;
	}
	else
		cout << "Meshes detected" << endl;

	aiNode* iRoot = scene->mRootNode;

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
	rootTransform->SetSca(D3DXVECTOR3(scaleRoot.x, scaleRoot.y, scaleRoot.z));

	for (unsigned int i = 0; i < iRoot->mNumChildren; i++)
	{
		ImportChildren(iRoot->mChildren[i], root, scene, dev);
	}
}

void SceneImporter::ImportChildren(aiNode * child, Composite* parent, const aiScene * scene, LPDIRECT3DDEVICE9 dev)
{
	aiVector3D position;
	aiQuaternion rotation;
	aiVector3D scale;
	D3DXVECTOR3 rotAxis;
	float angle;

	child->mTransformation.Decompose(scale, rotation, position);

	D3DXQUATERNION auxQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);

	D3DXQuaternionToAxisAngle(&auxQuaternion, &rotAxis, &angle);

	D3DXVec3Normalize(&rotAxis, &rotAxis);

	Composite* newComp = new Composite();

	newComp->SetName(child->mName.C_Str());

	//cout << "Cargando " << newComp->GetName() << " hijo de " << parent->GetName() << endl;

	Model* newModel = new Model();
	Material* newMat = new Material(L"BoxTest.png", dev);
	MeshRenderer* newMeshRenderer = new MeshRenderer(newModel, newMat);
	Transform* newTrans = new Transform();


	newComp->Add(newMeshRenderer);
	newComp->Add(newTrans);

	newTrans->SetPos(position.x, position.y, position.z);
	newTrans->SetRot(rotAxis.x * angle, rotAxis.y * angle, rotAxis.z * angle);

	newTrans->SetSca(scale.x, scale.y, scale.z);

	parent->Add(newComp);

	for (unsigned int i = 0; i < child->mNumMeshes; i++)
	{
		const aiMesh* rootModel = scene->mMeshes[child->mMeshes[i]];

		BoundingBox newBB;

		for (unsigned int j = 0; j < rootModel->mNumVertices; j++)
		{
			Vertex newVertex;

			newVertex.x = rootModel->mVertices[j].x;
			newVertex.y = rootModel->mVertices[j].y;
			newVertex.z = rootModel->mVertices[j].z;
			newVertex.nx = rootModel->mNormals[j].x;
			newVertex.ny = rootModel->mNormals[j].y;
			newVertex.nz = rootModel->mNormals[j].z;
			newVertex.tu = rootModel->mTextureCoords[0][j].x;
			newVertex.tv = rootModel->mTextureCoords[0][j].y;

			newBB.xMin = min(rootModel->mVertices[j].x, newBB.xMin);
			newBB.yMin = min(rootModel->mVertices[j].y, newBB.yMin);
			newBB.zMin = min(rootModel->mVertices[j].z, newBB.zMin);
			newBB.xMax = max(rootModel->mVertices[j].x, newBB.xMax);
			newBB.yMax = max(rootModel->mVertices[j].y, newBB.yMax);
			newBB.zMax = max(rootModel->mVertices[j].z, newBB.zMax);

			newModel->vertexes.push_back(newVertex);
		}

		newBB.Refresh();
		newModel->SetBB(newBB);

		for (unsigned int k = 0; k < rootModel->mNumFaces; k++)
		{
			const aiFace meshFace = rootModel->mFaces[k];

			for (int l = 0; l < 3; l++)
			{
				newModel->indexes.push_back(meshFace.mIndices[l]);
			}
		}

		LPDIRECT3DINDEXBUFFER9 ib;
		LPDIRECT3DVERTEXBUFFER9 vb;
		dev->CreateVertexBuffer(newModel->vertexes.size() * sizeof(Vertex), 0, MYFVF, D3DPOOL_MANAGED, &vb, NULL);
		dev->CreateIndexBuffer(newModel->indexes.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, NULL);

		VOID* lockedData = NULL;
		vb->Lock(0, 0, (void**)&lockedData, 0);
		memcpy(lockedData, newModel->vertexes.data(), newModel->vertexes.size() * sizeof(Vertex));
		vb->Unlock();

		ib->Lock(0, 0, (void**)&lockedData, 0);
		memcpy(lockedData, newModel->indexes.data(), newModel->indexes.size() * sizeof(WORD));
		ib->Unlock();

		dev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		newModel->SetIndexBuffer(ib);
		newModel->SetVertexBuffer(vb);
	}

	if (child->mNumChildren > 0)
	{
		for (unsigned int i = 0; i < child->mNumChildren; i++)
		{
			ImportChildren(child->mChildren[i], newComp, scene, dev);
		}
	}
}