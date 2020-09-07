#pragma once
#include "RenderComponent.h"
class FullRenderer :
	public RenderComponent
{
public:
	FullRenderer(Texture* image);
	virtual ~FullRenderer();
	virtual void render(GameObject* o, Uint32 time);
private:
	Texture * image_;
};

