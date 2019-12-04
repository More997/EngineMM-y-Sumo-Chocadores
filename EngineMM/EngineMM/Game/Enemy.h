#pragma once
#include "Character.h"
class Enemy : public Character
{
protected:
	/*static*/ int enemyNumber = 0;
public:
	Enemy();
	~Enemy();
	void aim(int playerPosX, int playerPosY);
	void fire();
	void Damage();
	void Death();
	void move();
};

