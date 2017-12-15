#include "stdafx.h"
#include "Perseguidor.h"


Perseguidor::Perseguidor()
{
	x = 0;
	y = 0;
	setVector(D3DXVECTOR3(x, y, 1));
	mov = true;
}


Perseguidor::~Perseguidor()
{
}



void Perseguidor::setX(float _X)
{
	x = _X;
}

float Perseguidor::getX()
{
	return x;
}

void Perseguidor::setY(float _Y)
{
	y = _Y;
}

float Perseguidor::getY()
{
	return y;
}


void Perseguidor::derrota()
{
	mov = false;
}
