#ifndef PERSEGUIDOR_H
#define PERSEGUIDOR_H
#include "../EngineMM/ConectorDeEngine.h"
#include "../EngineMM/Animacion.h"
#include "../EngineMM/Camera.h"
#include "../EngineMM/Tilemap.h"
#include "../EngineMM/MeshRender.h"
class Perseguidor
{
private:
	float velMax;
	float vel;
	float velMin;
	float sumavel;
	float x;
	float y;
	Animacion * animacion;
	Composite* perse;
	Mesh* mesh;
	Textura* tex;
	bool mov;
public:
	Perseguidor();
	~Perseguidor();
	void setVel(float _vel);
	float getVel();
	void setX(float _X);
	float getX();
	void setY(float _Y);
	float getY();
	void masVel();
	void movimiento(float xPJ, float yPJ);
	void derrota();
	
};
#endif

