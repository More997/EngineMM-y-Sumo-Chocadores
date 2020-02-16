#ifndef GRANADAGAME_H
#define GRANADAGAME_H
#include "Game.h"
/*
#include "MeshRenderer.h"
#include "Model.h"
#include "Material.h"
*/
class GameTest : public Game
{
private:
	
	Composite* a;
	Transform* aTransform;
	
	MeshRenderer* aMeshR;
	
	Model* aModel;
	Material* aMaterial;
	
public:
	void LoadContent(LPDIRECT3DDEVICE9 dev) override;
	void Update(LPDIRECT3DDEVICE9 dev) override;

	~GameTest();
};
#endif
