#include "stdafx.h"
#include "Perseguidor.h"


Perseguidor::Perseguidor()
{
	x = 0;
	y = 0;
	vel = velMin = 0;
	velMax = 2.0f;
	sumavel = 0.005F;
	mesh = new Mesh();
	tex = new Textura(L"Perseguidor.png");
	animacion = new Animacion(tex);
	perse = new Composite();
	animacion->SetMesh(mesh);
	perse->setModelScale(1, 1, 1);
	perse->setVector(D3DXVECTOR3(x, y, 2));
	perse->Add(animacion);
	animacion->addFrames(2, 2);
	mov = true;
}


Perseguidor::~Perseguidor()
{
}

void Perseguidor::setVel(float _vel)
{
	vel = _vel;
}

float Perseguidor::getVel()
{
	return vel;
}

void Perseguidor::setX(float _X)
{
	x = _X;
	perse->setModelPos(x, y, 1);
}

float Perseguidor::getX()
{
	return x;
}

void Perseguidor::setY(float _Y)
{
	y = _Y;
	perse->setModelPos(x, y, 1);
}

float Perseguidor::getY()
{
	return y;
}


void Perseguidor::movimiento(float xPJ, float yPJ)
{
	if (mov == true)
	{
		if (xPJ >= x)
		{
			x += vel;
		}
		else if (xPJ < x)
		{
			x -= vel;
		}
		if (yPJ >= y)
		{
			y += vel;
		}
		else if (yPJ < y)
		{
			y -= vel;
		}
	}
	perse->setModelPos(x, y, 1);
	if (vel != velMax)
	{
		vel += sumavel;
	}
	perse->Render();	
}

void Perseguidor::derrota()
{
	mov = false;
}
