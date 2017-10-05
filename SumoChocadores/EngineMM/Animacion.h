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

	float lastFrameMs;
	float minFrameTime;
	float FrameporSec = 60;
	vector <Vertex> _vertex;
	int animationPosition;
	vector<Mesh*> spritesheet;
public:
	Animacion(Textura* tex);
	~Animacion();
	float getMS();
	void Update();
	void setFramesPerSec(int frames);
	void addFrames (int spriteColum, int spriteFila);
};
#endif

