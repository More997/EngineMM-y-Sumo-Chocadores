#include "stdafx.h"
#include "MeshRenderer.h"
#include "Game.h"


MeshRenderer::MeshRenderer(Camera* _theCamera)
{
	theCamera = _theCamera;
	//importedModel = 0;
}
MeshRenderer::MeshRenderer(Mesher* comingMesher)
{
	theMesher = comingMesher;
}
MeshRenderer::MeshRenderer(Mesher * comingMesher, Camera * _theCamera)
{
	theCamera = _theCamera;
	//importedModel = 0;
	theMesher = comingMesher;
}
MeshRenderer::MeshRenderer(Texture* thatTexture, Camera* _theCamera)
{
	theTexture = thatTexture;
	theCamera = _theCamera;
}
MeshRenderer::MeshRenderer(Mesher * comingMesher, Texture * thatTexture, Camera * _theCamera)
{
	theCamera = _theCamera;
	//importedModel = comingMesher; // modificado para graficos III
	theMesher = comingMesher;
	theTexture = thatTexture;
}
MeshRenderer::~MeshRenderer()
{
}
void MeshRenderer::SetMesher(Mesher*_theMesher)
{
	theMesher = _theMesher;
}
Mesher * MeshRenderer::GetMesher()
{
	return theMesher;
}
void MeshRenderer::defineTransformationMatrix()
{
	Composite::defineTransformationMatrix();
}
void MeshRenderer::SetTexture(Texture *tex)
{
	theTexture = tex;
}
BoundingBox MeshRenderer::GetMeshBoundingBox()
{
	return theMesher->GetBoundingBoxByCopy();
}
Texture* MeshRenderer::GetTexture()
{
	return theTexture;
}
bool MeshRenderer::BoxinFructrum()
{
	Game* s = Game::getInstance();
	//http://www.chadvernon.com/blog/resources/directx9/frustum-culling/
	//http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-testing-boxes/
	//http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-testing-boxes-ii/
	//int result = 0; // 0 = inside, 1 = out, 2 = in
	vector<D3DXPLANE> fructrumVector = theCamera->GetFructrumVector();
	BoundingBox checkBox = GetBoundingBox(); //GetMeshBoundingBox()

	for (int i = 0; i < 6; i++) // 6 u 8?
	{

		if (((fructrumVector[i].a * checkBox.xMin) + (fructrumVector[i].b * checkBox.yMin) + (fructrumVector[i].c * checkBox.zMin) + (fructrumVector[i].d) < 0) &&
			((fructrumVector[i].a * checkBox.xMax) + (fructrumVector[i].b * checkBox.yMin) + (fructrumVector[i].c * checkBox.zMin) + (fructrumVector[i].d) < 0) &&
			((fructrumVector[i].a * checkBox.xMax) + (fructrumVector[i].b * checkBox.yMax) + (fructrumVector[i].c * checkBox.zMin) + (fructrumVector[i].d) < 0) &&
			((fructrumVector[i].a * checkBox.xMin) + (fructrumVector[i].b * checkBox.yMax) + (fructrumVector[i].c * checkBox.zMin) + (fructrumVector[i].d) < 0) &&
			((fructrumVector[i].a * checkBox.xMin) + (fructrumVector[i].b * checkBox.yMin) + (fructrumVector[i].c * checkBox.zMax) + (fructrumVector[i].d) < 0) &&
			((fructrumVector[i].a * checkBox.xMax) + (fructrumVector[i].b * checkBox.yMin) + (fructrumVector[i].c * checkBox.zMax) + (fructrumVector[i].d) < 0) &&
			((fructrumVector[i].a * checkBox.xMin) + (fructrumVector[i].b * checkBox.yMax) + (fructrumVector[i].c * checkBox.zMin) + (fructrumVector[i].d) < 0) &&
			((fructrumVector[i].a * checkBox.xMax) + (fructrumVector[i].b * checkBox.yMax) + (fructrumVector[i].c * checkBox.zMax) + (fructrumVector[i].d) < 0)
			) //Ecuaciones del proyecto, hechas en cada uno de los planos de fructrum
		{
			//s->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, /*D3DCOLOR_XRGB(255, 0, 0)*/ D3DCOLOR_ARGB(100, 100, 100, 100), 1.0f, 0);

			return false; //FALSE

		}

	}
	//
	/*
	Normales:
	Left: Mira hacia adentro (ahora).
	Right: Mira hacia adentro.
	Top: Mira hacia adentro.
	Bottom: Mira hacia adentro.
	Near: Mira hacia adentro.
	Far: ¿Me retorna 0?


	*/
	//
		if ((fructrumVector[5].a * checkBox.xMin) + (fructrumVector[5].b * checkBox.yMin) + (fructrumVector[5].c * checkBox.zMin) + (fructrumVector[5].d) == 0)
	{
		//s->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, /*D3DCOLOR_XRGB(255, 0, 0)*/ D3DCOLOR_ARGB(100, 100, 100, 100), 1.0f, 0);
		return false; //FALSE
	   }
	

	//s->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, /*D3DCOLOR_XRGB(255, 0, 0)*/ D3DCOLOR_ARGB(0, 0, 0, 100), 1.0f, 0);
	return true; //TRUE
}
//SetProjection



void MeshRenderer::Blending(int blendNumber)
{
	Game* s = Game::getInstance();
	switch (blendNumber)
	{
	case 0://Aditivo
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		s->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		s->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case 1: //Multiplicativo
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		s->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		s->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	case 2://alphaBlending
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		s->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		s->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	default:
		s->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		break;
	}
}

void MeshRenderer::RenderingComposite()
{

	if (BoxinFructrum() == true)
	{
		Game* s = Game::getInstance();
		if (theTexture != NULL)
			s->GetDevice()->SetTexture(0, theTexture->GetTexture()); //"Pinta" el objeto textura.
		else
			s->GetDevice()->SetTexture(0, NULL); //Limpia el objeto textura

		s->GetDevice()->SetFVF(MYFVF);


		//Le digo a la placa que la matriz de mundo es "mat"

		//if model = null
		s->GetDevice()->SetTransform(D3DTS_WORLD, &GetTransformationMatrix());

		s->GetDevice()->SetFVF(MYFVF);
		s->GetDevice()->SetStreamSource(0, theMesher->GetVb(), 0, sizeof(Vertex));
		s->GetDevice()->SetIndices(theMesher->GetIb());
		s->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, theMesher->vertexes.size(), 0, theMesher->indexesVector.size() / 3);
	}
	else
	{
		std::cout << "No esta en camara, así que no se renderiza." << std::endl;
	}
}