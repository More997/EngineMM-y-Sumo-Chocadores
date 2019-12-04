#pragma once
class Item
{
protected:
	int x;
	int y;
public:
	Item();
	~Item();
	int GetX();
	int GetY();
	void SetX(int _x);
	void SetY(int _y);
	void Disappear();
};