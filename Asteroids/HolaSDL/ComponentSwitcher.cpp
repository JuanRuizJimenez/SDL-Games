#include "ComponentSwitcher.h"
#include "XboxController.h"

ComponentSwitcher::ComponentSwitcher(SDLGame* game, Fighter* o, SDL_Keycode key) :
		GameObject(game), o_(o), key_(key), modes_(), currMode_(-1) {
}

ComponentSwitcher::~ComponentSwitcher() {
}

void ComponentSwitcher::handleInput(Uint32 time, const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == key_) {
		switchToNextMode();
	}

	else if (XboxController::Instance()->getNumControllers() > 0) {
		if (event.type == SDL_JOYBUTTONDOWN)
		{
			XboxController::Instance()->onJoystickButtonDown(event);

			if (XboxController::Instance()->getButtonState(0, 0)) //A button
			{
				switchToNextMode();
			}

			XboxController::Instance()->onJoystickButtonUp(event);
			if (event.type == SDL_JOYBUTTONUP)
				XboxController::Instance()->onJoystickButtonUp(event);
		}
	}
}

void ComponentSwitcher::update(Uint32 time) {
}

void ComponentSwitcher::render(Uint32 time) {
	if ( currMode_ != -1 && modes_[currMode_].iconRC != nullptr) {
		modes_[currMode_].iconRC->render(this, time);
	}
}

void ComponentSwitcher::addMode(ModeInfo mode) {
	modes_.push_back(mode);
}

void ComponentSwitcher::switchToNextMode() {
	setMode( (currMode_ + 1) % modes_.size() );
}

void ComponentSwitcher::setMode(int i) {
	ModeInfo m;

	if ( currMode_ != -1 ) {
		m = modes_[currMode_];
		if ( m.ic != nullptr ) {
			o_->delInputComponent(m.ic);
		}
		if (m.ic2 != nullptr) {
			o_->delInputComponent(m.ic2);
		}
		if (m.ic3 != nullptr) {
			o_->delInputComponent(m.ic3);
		}
		if ( m.pc != nullptr ) {
			o_->delPhysicsComponent(m.pc);
		}
		if ( m.rc != nullptr ) {
			o_->delRenderComponent(m.rc);
		}
	}

	currMode_ = i;
	o_->setId(currMode_);
	m =  modes_[currMode_];;
	if ( m.ic != nullptr ) {
		o_->addInputComponent(m.ic);
	}
	if (m.ic2 != nullptr) {
		o_->addInputComponent(m.ic2);
	}
	if (m.ic3 != nullptr) {
		o_->addInputComponent(m.ic3);
	}
	if ( m.pc != nullptr ) {
		o_->addPhysicsComponent(m.pc);
	}
	if ( m.rc != nullptr ) {
		o_->addRenderComponent(m.rc);
	}
}
