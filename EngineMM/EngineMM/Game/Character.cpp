#include "stdafx.h"
#include "Character.h"


Character::Character()
{
}


Character::~Character()
{
}

int Character::GetX()
{
	return x;
}

int Character::GetY()
{
	return y;
}

void Character::setX(int _x)
{
	x = _x;
}

void Character::setY(int _y)
{
	y = _y;
}

void Character::Death()
{
}

int Character::getHealth()
{
	return 0;
}
