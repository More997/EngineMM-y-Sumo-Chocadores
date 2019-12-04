#ifndef GAMEMMPLAY_H
#define GAMEMMPLAY_H
#include "../Engine/GameInterface.h"
#include "../Engine/Input.h"
#include "../Engine/MeshRenderer.h"
#include "../Engine/Animated.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/SceneImporter.h"
#include "../Engine/TileSet.h"
#include "../Engine/TileRenderer.h"
#include "../Engine/BSP.h"
class GameMMPlay : public GameInterface
{
private:
	Game *game;
	Composite* root;
	Composite* playerCube;
	Composite *principalCamera;
	Camera *cameraView;
	LPD3DXEFFECT shaderEffect;
	int passesNumber;
	Input *gameInput;
	
	Composite *island;
	SceneImporter *importer;
	BSP* bsp;
	list<Composite*> objectsToDraw;
	
	Composite *paul;
	Mesher *paulMesher;
	MeshRenderer *paulRenderer;
	Texture *paulTexture;
	Animated* paulAnimation;
	float paulXPositionToSet;

	TileSet *tileSet;
	TileRenderer *tileRenderer;
	BoundingBox* boxForTiler;
	
	map<string, vector<int>> reciverMap;
	vector<int> *intVectorInputUp;
	vector<int> *intVectorInputLeft;
	vector<int> *intVectorInputRight;
	vector<int> *intVectorInputDown;
	vector<int> *intVectorInputSpace;

	vector<int>*vUp;
	
	float numY;
	float numX;
	float numZ;
	float extraNum;
	
	Composite* bondi;
	Mesher* bondiMesher;
	Texture* bondiTexture;
	MeshRenderer* bondiRenderer;

	Composite* compositeSon;
	Mesher* sonsMesher;
	Texture* sonsTexture;
	MeshRenderer* sonsRenderer;

	BoundingBox forTesting;
	


public:
	GameMMPlay();
	~GameMMPlay();
	void SetRoot(Composite* _root);
	void LoadContent();
	void FrameEvent();
};
#endif