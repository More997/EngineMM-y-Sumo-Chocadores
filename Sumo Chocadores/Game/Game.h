#ifndef GRANADAGAME_H
#define GAME_H
#include "GameTest.h"

class Game : public GameTest
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

	~Game();
};
#endif
