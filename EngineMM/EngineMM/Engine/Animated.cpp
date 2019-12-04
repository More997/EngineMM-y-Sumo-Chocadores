#include "stdafx.h"
#include "Animated.h"

Animated::Animated(Texture* thatTexture, Camera* theCamera) : MeshRenderer(thatTexture, theCamera) //revisar
{
	animationPosition = 0;
	lastFrameMs = getMs();
}
Animated::~Animated()
{
}
int Animated::getMs() // Mas adelante hacer una clase timer que se ocupe de devolverlo.
{
	time_point<system_clock> actualTime = system_clock::now();
	system_clock::duration duration = actualTime.time_since_epoch();
	milliseconds ms = duration_cast<milliseconds>(duration);
	return ms.count();
}
void Animated::UpdateAnimation(float animationDeacceleration)
{
	actualMs = getMs();
	deltaTime = (actualMs - lastFrameMs) / 1000.0f;
	lastFrameMs = actualMs;
	spritetime += deltaTime;

	//animationPosition = (int)num;
	//animationPosition %= 2;
	if (spritetime >= animationDeacceleration)
	{
		spritetime = 0;
		//if (animationPosition <= /*4*/(sizeof(frames) - 2 ))
		if (animationPosition < frames.size()-1)
			animationPosition++;
		else
			animationPosition = 0;
		SetMesher(frames[animationPosition]);
	}
	//Render();
	//Draw();
}
void Animated::AddFrameAnimation(/*float startPositionX, float startPositionY, float fullX, /*float fullY, int frameWidth, int frameHeight,*/ int colNumber, int rowNumber /*Vertex unosVertex[], WORD comingIndexes[], */)
{
	
	tileXAmount = colNumber;
	tileYAmount = rowNumber;
	aspectRatio = (float)tileXAmount / (float)tileYAmount;
	float width = 1 / aspectRatio;

	tileWidth = 1.0f / tileXAmount;
	tileHeight = 1.0f / tileYAmount;

	tileRow = 1;
	tileCol = 1;
	//int toAdvance = tileCol;
	
	
	WORD indexes[] = { 3,0,1,3,1,2 };

	for (int i = 0; i < tileXAmount; i++)
	{
		//if(i > 0)
			tileCol++/* += toAdvance*/;
		Vertex vertexes2[4] =
		{
			{ 0.00f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, tileWidth * tileCol     , tileHeight * (tileRow + 1) },
			{ -width, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, tileWidth * (tileCol - 1) , tileHeight * (tileRow + 1) },
			{ -width, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, tileWidth * (tileCol - 1) , tileHeight * tileRow },
			{ 0.00f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, tileWidth * tileCol     , tileHeight * tileRow }
		};
		//frames[i] = new Mesher(vertexes2, indexes);
		frames.push_back(new Mesher(vertexes2, indexes));
		//SetMesher(frames[i]);
	}
	tileRow++;
	
	/*
	for (int i = 0; i < frameNumber; i++)
	{
		unosVertex->uv += 0.166;
		unosVertex->tu += 0.166;

		frames[i] = new Mesher(unosVertex, comingIndexes);
	}
	*/
	//Mesher* testMesh = new Mesher(vertexes2, indexes);
	//SetMesher(testMesh);
	//for (int i = 0; i < framesX; i++)
	//{
		//crear Mesher()
		//Mesher* aMesher = new Mesher(unVertex)
		/* { STARTPOSITIONX, +0.5f, 0.0f, 0.0f, 0.0f},
		{ +0.5f, +0.5f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },
		{ +0.5f, -0.5f, 0.0f, 1.0f, 1.0f },*/
		//Mesher FrameMesh = new Mesher(vertex); 
		//meshVector.push_back();
		//STARTpOSITIONx += width;
		//SetMesher(el Mesh del frame que me toca dibujar);
	//}

	/*tileRow = 1;
	tileCol = 1;*/

}


