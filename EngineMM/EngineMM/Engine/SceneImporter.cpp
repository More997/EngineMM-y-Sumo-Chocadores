#include "stdafx.h"
#include "SceneImporter.h"
#include "Transform.h"
#include "MeshRenderer.h"

SceneImporter::SceneImporter()
{
	s = Game::getInstance();
	std::cout << "SceneImporter arranca" << std::endl;
}


SceneImporter::~SceneImporter()
{
}

void SceneImporter::ImportScene(const std::string& pFile, Composite* root, Camera* objectCamera/*, LPDIRECT3DDEVICE9 dev*/) //A dev lo geteamos de Game
{
	
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	//bounding.xMin = scene.

	// = xMin = min(position.x, boundi.xMin); // ?????????

	// If the import failed, report it
	if (!scene)
	{
		//DoTheErrorLogging(importer.GetErrorString());

		std::cout << "Import test failed" << std::endl;

		return;
	}
	if (!scene->HasMeshes())
	{
		std::cout << "The scene does not have meshes" << std::endl;
	}
	else
		std::cout << "The scene does have meshes" << std::endl;
	
	aiNode* iRoot = scene->mRootNode;
	root->SetName(iRoot->mName.C_Str());
	
	if (iRoot->mNumChildren <= 0 && iRoot->mNumMeshes <= 0) //Si no hay mas que hacer, se termina acá.
		return;

	Transform* rootTransform = new Transform();
	root->Add(rootTransform);

	aiVector3D positionRoot;
	aiQuaternion rotationRoot;
	aiVector3D scaleRoot;

	iRoot->mTransformation.Decompose(scaleRoot, rotationRoot, positionRoot); //Preguntar exactamente que es

	rootTransform->SetPos(D3DXVECTOR3(positionRoot.x, positionRoot.y, positionRoot.z));
	rootTransform->SetRot(D3DXVECTOR3(0, 0, 0));
	rootTransform->SetSca(D3DXVECTOR3(scaleRoot.x, scaleRoot.y, scaleRoot.z));

	for (unsigned int i = 0; i < iRoot->mNumChildren; i++)
	{
		ImportChildren(iRoot->mChildren[i], root, scene, objectCamera); //Importo a los hijos de a uno, y los agrego al root.
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

	if (child->mNumChildren <= 0 && child->mNumMeshes <= 0) //Si no hay mas que hacer, se termina acá.
		return;

	cout << "Cargando " << newComp->GetName() << " hijo de " << parent->GetName() << endl;

	Mesher* newMesher = new Mesher();
	Texture* newTex = new Texture(L"grass.jpg");
	MeshRenderer* newMeshRenderer = new MeshRenderer(newMesher, newTex, objectCamera);
	Transform* newTrans = new Transform();

	newComp->Add(newMeshRenderer);
	newComp->Add(newTrans);

	newTrans->SetPos(position.x, position.y, position.z);
	newTrans->SetRot(rotAxis.x * angle, rotAxis.y * angle, rotAxis.z * angle);

	newTrans->SetSca(scale.x, scale.y, scale.z);

	newComp->SetModelPosition(newTrans->GetPos().x, newTrans->GetPos().y, newTrans->GetPos().z);
	newComp->SetModelRotation(newTrans->GetRot().x, newTrans->GetRot().y, newTrans->GetRot().z);
	newComp->SetModelScale(newTrans->GetScaleX(), newTrans->GetScaleY(), newTrans->GetScaleZ());

	cout << "La posicion de este objeto es de: " << newComp->GetPosition().x << endl;

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

			newMesher->vertexes.push_back(newVertex);
		}

		newBB.Refresh();
		newMesher->SetBoundingBox(newBB);
		newComp->SetBoundingBox(newMesher->GetBoundingBox());


		for (unsigned int k = 0; k < rootModel->mNumFaces; k++)
		{
			const aiFace meshFace = rootModel->mFaces[k];

			for (int l = 0; l < 3; l++)
			{
				newMesher->indexesVector.push_back(meshFace.mIndices[l]);
			}
		}

		LPDIRECT3DINDEXBUFFER9 ib;
		LPDIRECT3DVERTEXBUFFER9 vb;
		s->GetDevice()->CreateVertexBuffer(newMesher->vertexes.size() * sizeof(Vertex), 0, MYFVF, D3DPOOL_MANAGED, &vb, NULL);
		s->GetDevice()->CreateIndexBuffer(newMesher->indexesVector.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, NULL);

		VOID* lockedData = NULL;
		vb->Lock(0, 0, (void**)&lockedData, 0); //vb me da null?
		memcpy(lockedData, newMesher->vertexes.data(), newMesher->vertexes.size() * sizeof(Vertex));
		vb->Unlock();

		ib->Lock(0, 0, (void**)&lockedData, 0);
		memcpy(lockedData, newMesher->indexesVector.data(), newMesher->indexesVector.size() * sizeof(WORD));
		ib->Unlock();

		s->GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		/*dev->SetRenderState(D3DRS_ZWRITEENABLE, true);
		dev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);*/

		newMesher->SetIb(ib);
		newMesher->SetVb(vb);
	}

	if (child->mNumChildren > 0)
	{
		for (unsigned int i = 0; i < child->mNumChildren; i++)
		{
			ImportChildren(child->mChildren[i], newComp, scene, objectCamera);
		}
	}
}