#pragma once
class Character
{
protected:
	int x;
	int y;
public:
	Character();
	~Character();
	int GetX();
	int GetY();
	void setX(int _x);
	void setY(int _y);
	virtual void Death();
	int getHealth();
	virtual void Damage() = 0;
};

