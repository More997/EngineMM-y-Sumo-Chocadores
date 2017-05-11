#pragma once
#include "Game.h"
class Actor
{
public:
	LPDIRECT3DINDEXBUFFER9 ind;
	LPDIRECT3DVERTEXBUFFER9 vb;
	Actor();
	Actor(LPDIRECT3DDEVICE9 dev);
	~Actor();
	void DrawV(LPDIRECT3DDEVICE9 dev);
};

