#ifndef ANIMACION_H
#define ANIMACION_H
#include "MeshRender.h"
#include <chrono>
#include "Game.h"
#include "MeshRender.h"
using namespace std::chrono;
class IMPORTEXPORT Animacion :
	public MeshRender
{
private: 
	int tileXAmount;
	int tileYAmount;
	float aspectRatio;
	float width;
	float height;

	float tileWidth;
	float tileHeight;

	int tileFila;
	int tileCol;

	int lastFrameMs;
	float minFrameTime;
	float FrameporSec = 60;
	vector <Vertex> _vertex;
	int animationPositionX;
	vector<Mesh*> spritesheet;
	float actualMs;
	float deltaTime;
	float spriteTime = 0;
public:
	Animacion(Textura* tex);
	~Animacion();
	int getMS();
	void UpdateAn(float num);
	void setFramesPerSec(int frames);
	void addFrames (int spriteColum, int spriteFila);
};
#endif

