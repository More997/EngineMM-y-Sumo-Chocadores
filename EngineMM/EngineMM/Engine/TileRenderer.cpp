#include "stdafx.h"
#include "TileRenderer.h"

TileRenderer::TileRenderer(Camera* _theCamera) : MeshRenderer(_theCamera)
{
}
TileRenderer::~TileRenderer()
{
}
void TileRenderer::SetTiler(TileSet& thyTiles)
{
	seinTiles = &thyTiles;
}

void TileRenderer::Move(D3DXVECTOR3 trasl, D3DXVECTOR3 escal, D3DXVECTOR3 rot)
{
	Composite::SetModelPosition(trasl.x, trasl.y, trasl.z);
	Composite::SetModelRotation(rot.x, rot.y, rot.z);
	Composite::SetModelScale(escal.x, escal.y, escal.z);
	
	seinTiles->SetModelPosition(trasl.x, trasl.y, trasl.z);
	seinTiles->SetModelRotation(rot.x, rot.y, rot.z);
	seinTiles->SetModelScale(escal.x, escal.y, escal.z);
}
TileSet &TileRenderer::GetTiler()
{
	return *seinTiles;
}
BoundingBox* TileRenderer::BringTiler()
{
	return seinTiles->GetBoundingBox();
}
vector<vector<BoundingBox*>> TileRenderer::BringBoxes()
{
	return seinTiles->GetLasCajitas();
}
bool TileRenderer::CheckFrustrumTile(vector<D3DXPLANE> elFrustrum)
{
	BoundingBox checkBox = *BringTiler();

	for (int i = 0; i < 6; i++)
	{
		if (((elFrustrum[i].a * checkBox.xMin) + (elFrustrum[i].b * checkBox.yMin) + (elFrustrum[i].c * checkBox.zMin) + (elFrustrum[i].d) < 0) &&
			((elFrustrum[i].a * checkBox.xMax) + (elFrustrum[i].b * checkBox.yMin) + (elFrustrum[i].c * checkBox.zMin) + (elFrustrum[i].d) < 0) &&
			((elFrustrum[i].a * checkBox.xMax) + (elFrustrum[i].b * checkBox.yMax) + (elFrustrum[i].c * checkBox.zMin) + (elFrustrum[i].d) < 0) &&
			((elFrustrum[i].a * checkBox.xMin) + (elFrustrum[i].b * checkBox.yMax) + (elFrustrum[i].c * checkBox.zMin) + (elFrustrum[i].d) < 0) &&
			((elFrustrum[i].a * checkBox.xMin) + (elFrustrum[i].b * checkBox.yMin) + (elFrustrum[i].c * checkBox.zMax) + (elFrustrum[i].d) < 0) &&
			((elFrustrum[i].a * checkBox.xMax) + (elFrustrum[i].b * checkBox.yMin) + (elFrustrum[i].c * checkBox.zMax) + (elFrustrum[i].d) < 0) &&
			((elFrustrum[i].a * checkBox.xMin) + (elFrustrum[i].b * checkBox.yMax) + (elFrustrum[i].c * checkBox.zMin) + (elFrustrum[i].d) < 0) &&
			((elFrustrum[i].a * checkBox.xMax) + (elFrustrum[i].b * checkBox.yMax) + (elFrustrum[i].c * checkBox.zMax) + (elFrustrum[i].d) < 0)
			) //Ecuaciones del proyecto, hechas en cada uno de los planos de fructrum
		{
			//s->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, /*D3DCOLOR_XRGB(255, 0, 0)*/ D3DCOLOR_ARGB(100, 100, 100, 100), 1.0f, 0);

			return false; //FALSE

		}

	}
	return true;
}
void TileRenderer::RenderingComposite()
{
	Game* s = Game::getInstance();
	// MeshRenderer::RenderingComposite();
	float anchoTile = 1.0f;
	float altoTile = 1.0f;

	D3DXMATRIX matSca;
	D3DXMatrixScaling(&matSca, anchoTile, altoTile, 1);
	s->GetDevice()->SetFVF(MYFVF);
	s->GetDevice()->SetStreamSource(0, seinTiles->GetVvb()[0], 0, sizeof(Vertex));
	s->GetDevice()->SetIndices(seinTiles->GetVib()[0]);

	vector<LPDIRECT3DTEXTURE9> palleteVector = seinTiles->GetPaletteVector();

	for (int i = 0; i < seinTiles->GetFilas(); i++)
	{
		vector<int> fila = seinTiles->GetA()[i];
		for (int j = 0; j < seinTiles->GetColumnas(); j++)
		{
			int thyCelda = fila.at(j);
			LPDIRECT3DTEXTURE9 tex;
			if (!palleteVector.empty())
			{ 
				tex = palleteVector.back();
				palleteVector.pop_back();
			}
			else
				tex = seinTiles->GetDefaultTexture();
			//LPDIRECT3DTEXTURE9 tex = seinTiles->GetPaletteVector[i,j];
			s->GetDevice()->SetTexture(0, tex);

			float posX = anchoTile * j;
			float posY = altoTile * i;
			D3DXMATRIX matTrans;
			D3DXMatrixTranslation(&matTrans, posX, -posY, 2);

			D3DXMATRIX mat = matSca * matTrans;
			s->GetDevice()->SetTransform(D3DTS_WORLD, &mat);
			// for (int k = 0; k <= BringBoxes().size() - 1; k++) 
// {
	// for (int j = 0; j <= BringBoxes()[k].size() - 1; j++) 
	// {
			if (CheckFrustrumTile(theCamera->GetFructrumVector()))
			{
				s->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, seinTiles->vVertexes[thyCelda].size()/*4*/, 0, seinTiles->vIndexes[thyCelda].size()/*2*/);
			}
			else
				std::cout << "No esta en camara, así que no se renderiza." << std::endl;
			// }
		// }
		}
	} 
}