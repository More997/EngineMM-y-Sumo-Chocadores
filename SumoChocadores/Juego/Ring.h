#ifndef RING_H
#define RING_H
#pragma once
#include <string>
#include <iostream>
using namespace std;
class Ring
{
private:
	string nombre;
	int x;
	int y;
public:
	Ring();
	void setX(int _x);
	int getX();
	void setNombre(string _nombre);
	string getNombre();
	int getY();
	void setY(int _y);
};
#endif