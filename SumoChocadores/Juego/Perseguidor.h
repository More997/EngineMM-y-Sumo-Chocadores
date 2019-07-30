#ifndef PERSEGUIDOR_H
#define PERSEGUIDOR_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
#include "../EngineMM/Camera.h"
#include "../EngineMM/MeshRender.h"
class Perseguidor :
	public Composite
{
private:
	float x;
	float y;
	bool mov;
public:
	Perseguidor();
	~Perseguidor();
	void setX(float _X);
	float getX();
	void setY(float _Y);
	float getY();
	void derrota();
};
#endif

