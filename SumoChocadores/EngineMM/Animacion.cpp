#include "stdafx.h"
#include "Animacion.h"




Animacion::Animacion(Textura * tex) : MeshRender (tex)
{
	animationPosition = 0;
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


void Animacion::Update()
{
	float actualMs = getMS();
	float deltaTime = (actualMs - lastFrameMs) / 1000.0f;
	lastFrameMs = actualMs;

	//animationPosition = (int)num;
	//animationPosition %= 2;
	if (lastFrameMs >= 0)
	{

		//if (animationPosition <= /*4*/(sizeof(frames) - 2 ))
		if (animationPosition < spritesheet.size() - 1)
			animationPosition++;
		else
			animationPosition = 0;
		SetMesh(spritesheet[animationPosition]);
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
	int toAdvance = tileCol;


	WORD indexes[] = { 3,0,1,3,1,2 };

	for (int i = 0; i < tileXAmount; i++)
	{
		if (i > 0)
			tileCol += toAdvance;
		Vertex vertexes2[4] =
		{
			{ 0.00f, 0.0f, 0.0f, tileWidth * tileCol     , tileHeight * (tileFila + 1) },
			{ -width, 0.0f, 0.0f, tileWidth * (tileCol - 1) , tileHeight * (tileFila + 1) },
			{ -width, 1.0f, 0.0f, tileWidth * (tileCol - 1) , tileHeight * tileFila },
			{ 0.00f, 1.0f, 0.0f, tileWidth * tileCol     , tileHeight * tileFila }
		};
		
		spritesheet.push_back(new Mesh(vertexes2, indexes));

	}
}

