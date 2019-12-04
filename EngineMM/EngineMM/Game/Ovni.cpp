#include "stdafx.h"
#include "Ovni.h"


Ovni::Ovni()
{
	lookingRight = true;
	lookingDown = true;
	x = 0;
	y = 0;
}

Ovni::~Ovni()
{
}

void Ovni::HorizontalBounce()
{
	if (lookingRight == false)
		lookingRight = true;
	else
		lookingRight = false;
}

void Ovni::VerticalBounce()
{
	if (lookingDown == false)
		lookingDown = true;
	else
		lookingDown = false;
}

bool Ovni::GetLookingRight()
{
	return lookingRight;
}

bool Ovni::GetLookingDown()
{
	return lookingDown;
}

float Ovni::GetX()
{
	return x;
}

float Ovni::GetY()
{
	return y;
}

void Ovni::SetX(float _x)
{
	x = _x;
}

void Ovni::SetY(float _y)
{
	y = _y;
}
