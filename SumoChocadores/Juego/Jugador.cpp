#include "stdafx.h"
#include "Jugador.h"


Jugador::Jugador()
{
	x = -0.5;
	y = -0.5;
	Mov = true;
	setVector(D3DXVECTOR3(x, y, 1));

}


Jugador::~Jugador()
{
}

void Jugador::setX(float _x)
{
	x = _x;
}

void Jugador::setY(float _y)
{
	y = _y;
}

float Jugador::getX()
{
	return x;
}

float Jugador::getY()
{
	return y;
}

void Jugador::GameOver()
{
	Mov = false;
}

void Jugador::Movimiento()
{
	
	
}
