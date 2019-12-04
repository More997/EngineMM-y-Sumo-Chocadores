#ifndef TILERENDERER_H
#define TILERENDERER_H
#include "Composite.h"
#include "MeshRenderer.h"
#include "TileSet.h"
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include "Vertex.h"
#include "Game.h"
//#include "Meshrenderer.h"
class IMPORTEXPORT TileRenderer : public MeshRenderer
{
private:
	TileSet* seinTiles;
	int offsetX;
	int offsetY;
public:
	TileRenderer(Camera* _theCamera);
	~TileRenderer();
	void SetTiler(TileSet &thyTiles);
	void SetDevPointer(LPDIRECT3DDEVICE9 devy);
	void Move(D3DXVECTOR3 trasl, D3DXVECTOR3 escal, D3DXVECTOR3 rot);
	// Revisar el check frustrum y hacer uno para el tile
	TileSet& GetTiler();
	BoundingBox* BringTiler();
	vector<vector<BoundingBox*>> BringBoxes();
	bool CheckFrustrumTile(vector<D3DXPLANE> elFrustrum);
	bool CheckFrustrumTile(vector<D3DXPLANE> elFrustrum, int line, int column);
	void RenderingComposite() override;
};
#endif
