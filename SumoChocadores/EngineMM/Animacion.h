#ifndef ANIMACION_H
#define ANIMACION_H
#include "MeshRender.h"
#include <chrono>
#include "Game.h"
using namespace std::chrono;
class IMPORTEXPORT Animacion :
	public MeshRender
{
private: 
	int tileXCant;
	int tileYCant;
	int tileFila;
	int tileColumna;
	float aspectRatio;
	float height;
	float width;
	float FrameporSec = 30;
	int lastFrame;
	float minFrameTime;
	vector<Mesh> spritesheet;
public:
	Animacion();
	Animacion(int tileXA, int tileYA, int tileF, int tileC);
	~Animacion();
	float getMS();
	void Draw();
	void Update();
	void setFramesPerSec(int frames);
	void addFrames (int spriteStartX, int spriteStartY, int spriteWidth, int spriteHeight,
							int spriteTotalX, int spriteTotalY, int totalframes);
};
#endif

