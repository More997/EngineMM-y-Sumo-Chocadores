#ifndef ANIMATED_H
#define ANIMATED_H
#include "MeshRenderer.h"
#include "Game.h"
#include "Mesher.h"
#include <chrono>
using namespace std::chrono;
class IMPORTEXPORT Animated :
	public MeshRenderer
{
private:
	vector<Mesher*> frames;

	int tileXAmount;
	int tileYAmount;
	float aspectRatio;
	float width;
	float height;

	float tileWidth;
	float tileHeight;

	int tileRow;
	int tileCol;

	float lastFrameMs;
	float minFrameTime;
	float FramesPerSecod = 60;

	float actualMs;
	float deltaTime;
	float spritetime;
	
	//Vertex miVertex[6]; //numero hardcodeado. REPARAR
	vector <Vertex> miVertex;
	int animationPosition;


	/*int currentFrame = (int)num;
	currentFrame %= 2;
	if (currentFrame == 0)
		dev->SetStreamSource(0, vb, 0, sizeof(Vertex));
	if (currentFrame == 1)
		dev->SetStreamSource(0, vb2, 0, sizeof(Vertex));
		*/
public:
	Animated(Texture* thatTexture, Camera* theCamera);
	~Animated();
	int getMs();
	void UpdateAnimation(float animationDeacceleration);
	void AddFrameAnimation(/*float startPositionX, float startPositionY, float fullX, /*float fullY, int frameWidth, int frameHeight,*/ int colNumber, int rowNumber /*Vertex unosVertex[], WORD comingIndexes[], */);
};
#endif