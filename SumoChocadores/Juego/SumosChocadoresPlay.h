#ifndef SUMOSCHOCADORESPLAY_H
#define SUMOSCHOCADORESPLAY_H
#include "../EngineMM/ConectorDeEngine.h"
class SumosChocadoresPlay :
	 public ConectorDeEngine
{
public:
	SumosChocadoresPlay();
	~SumosChocadoresPlay();
	void Create();
	void Update();
};
#endif
