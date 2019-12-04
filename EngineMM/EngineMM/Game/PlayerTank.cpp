#include "stdafx.h"
#include "PlayerTank.h"
#include "../Engine/Game.h"
PlayerTank* PlayerTank::instance = 0;
PlayerTank::PlayerTank()
{
}
PlayerTank* PlayerTank::GetInstance()
{
	if(instance == 0)
		instance = new PlayerTank();
	return instance;
}
void PlayerTank::Controls()
{
	/*
	if (Game::instance->theInput->GetKeyDown(intVectorInputUp) == true)
		y += 0.1;
	if (Game::instance->theInput->GetKeyDown(intVectorInputLeft) == true)
		x -= 0.1;
	if (Game::instance->theInput->GetKeyDown(intVectorInputRight) == true)
		x += 0.1;
	if (Game::instance->theInput->GetKeyUp(intVectorInputUp) == true)
		y -= 0.01;
	*/
}
void PlayerTank::Move()
{
}

void PlayerTank::Aim()
{
}

void PlayerTank::fire()
{
}

void PlayerTank::Damage()
{
}
void PlayerTank::Death()
{
}