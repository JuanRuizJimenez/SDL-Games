#include "FullRenderer.h"

FullRenderer::FullRenderer(Texture* image) : image_(image)
{
}

FullRenderer::~FullRenderer()
{
}

void FullRenderer::render(GameObject* o, Uint32 time) {
	SDL_Rect rect RECT(0, 0, o->getGame()->getWindowWidth(), o->getGame()->getWindowHeight());

	image_->render(o->getGame()->getRenderer(), rect);
}