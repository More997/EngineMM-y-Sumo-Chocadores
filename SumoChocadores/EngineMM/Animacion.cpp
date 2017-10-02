#include "stdafx.h"
#include "Animacion.h"



Animacion::Animacion()
{
}

Animacion::Animacion(int tileXA, int tileYA, int tileF, int tileC)
{
	tileXCant = tileXA;
	tileYCant = tileYA;
	tileFila = tileF;
	tileColumna = tileC;

	aspectRatio = (float)tileXCant / (float)tileYCant;
	width = 1 / aspectRatio;
	tileFila = 1.0f / tileXCant;
	tileColumna = 1.0f / tileYCant;
	lastFrame = getMS();
	minFrameTime = 0.167f;
}


Animacion::~Animacion()
{
}

float Animacion::getMS()
{
	time_point<system_clock> actualTime = system_clock::now();
	system_clock::duration duration = actualTime.time_since_epoch();
	milliseconds ms = duration_cast<milliseconds>(duration);
	return ms.count();
}

void Animacion::Draw()
{
	float actualMS = getMS();
	float deltatime = (actualMS - lastFrame) / 1000.0f;
	lastFrame = actualMS;
	int currentFrame = (int)FrameporSec;
	currentFrame %= 2;
}

void Animacion::Update()
{
}

void Animacion::setFramesPerSec(int frames)
{
	FrameporSec = frames;
}

void Animacion::addFrames(int spriteStartX, int spriteStartY, int spriteWidth, int spriteHeight,
								int spriteTotalX, int spriteTotalY, int totalframes)
{
	width = spriteWidth;
	height = spriteHeight;
	for (int i = 0; i < totalframes; i++)
	{
		
		spriteStartX += width;
		spriteWidth += width;
	}
}

