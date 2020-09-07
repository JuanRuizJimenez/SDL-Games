#include "SoundManager.h"
#include "messages.h"

SoundManager::SoundManager(SDLGame* game) : game_(game) {
	// TODO Auto-generated constructor stub
}

SoundManager::~SoundManager() {
	// TODO Auto-generated destructor stub
}

void SoundManager::receive(Message* msg) {
	switch (msg->id_) {
	case BULLET_CREATED:
		game_->getResources()->getSoundEffect(Resources::Shoott)->play(0);
		break;
	case BULLET_ASTROID_COLLISION:
		game_->getResources()->getSoundEffect(Resources::Explosion)->play(0);
		break;
	case ASTROID_FIGHTER_COLLISION:
		game_->getResources()->getSoundEffect(Resources::Death)->play(0);
		break;
	case ROUND_START:
		game_->getResources()->getMusic(Resources::BackgroundMusic)->play(-1);
		break;
	case ROUND_OVER:
		//game_->getResources()->getMusic(Resources::BackgroundMusic)->stop();
		game_->getResources()->getSoundEffect(Resources::Over)->play(0);
		break;
	}
}
