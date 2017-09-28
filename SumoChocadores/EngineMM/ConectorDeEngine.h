#ifndef CONECTORDEENGINE_H
#define CONECTORDEENGINE_H
#include "EngineMMAPI.h"
class IMPORTEXPORT ConectorDeEngine
{
public:
	ConectorDeEngine();
	~ConectorDeEngine();
	virtual void Create() = 0;
	virtual void Update() = 0;
};
#endif
