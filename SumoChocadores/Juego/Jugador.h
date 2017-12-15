#ifndef JUGADOR_H
#define JUGADOR_H
#include "../EngineMM/Composite.h"
#include "../EngineMM/Input.h"
class Jugador : public Composite
{
private:
	float x;
	float y;
	bool Mov;
	
public:
	Jugador();
	~Jugador();
	void setX(float _x);
	void setY(float _y);
	float getX();
	float getY();
	void GameOver();
	void Movimiento();
};
#endif
