#ifndef CONECTORDEENGINE_H
#define CONECTORDEENGINE_H
#include "EngineMMAPI.h"
class ConectorDeEngine
{
public:
	IMPORTEXPORT ConectorDeEngine();
	IMPORTEXPORT ~ConectorDeEngine();
	virtual void Create() = 0;
	virtual void Update() = 0;
};
#endif
