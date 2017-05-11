#pragma once
#include <string>
#include "../EngineMM/Game.h"
#include "../EngineMM/Actor.h"
using namespace std;
class Personaje
{
private:
	int vida;
	string nombre;
	int ataque;
	int defensa;
	int nivel;
public:
	Personaje();
	Personaje(int up, int down, int right, int left); 
	void setNombre(string _nombre);
	string getNombre();
	int getVida();
	void setVida(int _vida);
	void setAtaque(int _ataque);
	int getAtaque();
	void setDefensa(int _defensa);
	int getDefensa();
	void setNivel(int _nivel);
	int getNivel();
	void up();
	void down();
	void right();
	void left();
	void dibujar();
	~Personaje();
}; 

