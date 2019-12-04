#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H
#include "Texture.h"
#include "Composite.h"
class IMPORTEXPORT GameInterface
{
public:
	GameInterface();
	~GameInterface();
	virtual void SetRoot(Composite* _root) = 0;
	virtual void LoadContent() = 0;
	virtual void FrameEvent() = 0;
};
#endif