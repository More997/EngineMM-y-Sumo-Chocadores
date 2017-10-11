#include "stdafx.h"
#include "Animacion.h"




Animacion::Animacion(Textura * tex) : MeshRender (tex)
{
	animationPositionX = 0;
}

Animacion::~Animacion()
{
}

int Animacion::getMS()
{
	time_point<system_clock> actualTime = system_clock::now();
	system_clock::duration duration = actualTime.time_since_epoch();
	milliseconds ms = duration_cast<milliseconds>(duration);
	return ms.count();
}


void Animacion::UpdateAn(float num)
{
	actualMs = getMS();
	deltaTime = (actualMs - lastFrameMs) / 1000.0f;
	lastFrameMs = actualMs;
	spriteTime += lastFrameMs;
	//animationPosition = (int)num;
	//animationPosition %= 2;
	if (spriteTime >= actualMs * num)
	{
		//if (animationPosition <= /*4*/(sizeof(frames) - 2 ))
		spriteTime = 0;
		if (animationPositionX < spritesheet.size() - 1)
			animationPositionX++;
		else if (animationPositionX)
			animationPositionX = 0;
		SetMesh(spritesheet[animationPositionX]);
	}
	//Render();
	//Draw();
}

void Animacion::setFramesPerSec(int frames)
{
	FrameporSec = frames;
}

void Animacion::addFrames(int spriteWidth, int spriteHeight)
{
	tileXAmount = spriteWidth;
	tileYAmount = spriteHeight;
	aspectRatio = (float)tileXAmount / (float)tileYAmount;
	float width = 1 / aspectRatio;

	tileWidth = 1.0f / tileXAmount;
	tileHeight = 1.0f / tileYAmount;

	tileFila = 1;
	tileCol = 1;

	WORD indexes[] = { 3,0,1,3,1,2 };
	for (int o = 0; o < tileYAmount; o++)
	{
		for (int i = 0; i < tileXAmount; i++)
		{
			Vertex vertexes2[4] =
			{
				{ 0.00f, 0.0f, 0.0f, tileWidth * tileCol     , tileHeight * (tileFila + 1) },
				{ -width, 0.0f, 0.0f, tileWidth * (tileCol - 1) , tileHeight * (tileFila + 1) },
				{ -width, 1.0f, 0.0f, tileWidth * (tileCol - 1) , tileHeight * tileFila },
				{ 0.00f, 1.0f, 0.0f, tileWidth * tileCol     , tileHeight * tileFila }
			};
			spritesheet.push_back(new Mesh(vertexes2, indexes));
			tileCol++;
		}
		tileFila++;
	}
}

