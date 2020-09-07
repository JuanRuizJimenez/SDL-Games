#include "PacManObject.h"

PacManObject::PacManObject(Game2p0* g, PlayState* p) : GameObject(g) {
	play = p;
}

PacManObject::~PacManObject()
{
}
