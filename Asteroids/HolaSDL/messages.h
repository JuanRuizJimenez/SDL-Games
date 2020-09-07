#ifndef MESSAGES_H_
#define MESSAGES_H_

#include "Asteroid.h"
#include "Bullet.h"
#include "Fighter.h"
#include "Bonus.h"

enum MessageId {
	BULLET_ASTROID_COLLISION,
	BULLET_FIGHTER_COLLISION,
	ASTROID_FIGHTER_COLLISION,
	FIGHTER_SHOOT,
	GAME_OVER,
	ROUND_START,
	ROUND_OVER,
	BULLET_CREATED,
	NO_MORE_ATROIDS,
	BADGE_ON,
	BADGE_OFF,
	AGILE_ON,
	AGILE_OFF,
	BAR_SHOOT,
	RESTART_BAR,
	BAR_LIFE,
	RESTART_BARLIFE,
	UPLIFE,
	END_PARTY,
	FIGHTER_BONUS_COLLISION,
	CREATE_BONUS,
	SET_MODE
};

struct Message {
	Message(MessageId id) :
			id_(id) {
	}
	MessageId id_;
};

struct BulletAstroidCollision: Message {
	BulletAstroidCollision(Bullet* bullet, Asteroid* astroid, bool destroy) :
			Message(BULLET_ASTROID_COLLISION), bullet_(bullet), astroid_(
					astroid), destroy_(destroy) {
	}
	Bullet* bullet_;
	Asteroid* astroid_;
	bool destroy_;
};

struct FighterBonusCollision : Message {
	FighterBonusCollision(Bonus* bonus, Fighter* fighter) :
		Message(FIGHTER_BONUS_COLLISION),
		bonus_(bonus), fighter_(fighter) {
	}
	Bonus* bonus_;
	Fighter* fighter_;
};

struct CreateBonus : Message {
	CreateBonus(Asteroid* asteroid) :
		Message(CREATE_BONUS), asteroid_(asteroid) {
	}
	Asteroid* asteroid_;
};

struct SetMode : Message {
	SetMode(int mode) :
		Message(SET_MODE), mode_(mode) {
	}
	int mode_;
};

struct BulletFighterCollision: Message {
	BulletFighterCollision(Bullet* bullet, Fighter* fighter) :
			Message(BULLET_FIGHTER_COLLISION), bullet_(bullet), fighter_(
					fighter) {
	}
	Bullet* bullet_;
	Fighter* fighter_;
};

struct AstroidFighterCollision: Message {
	AstroidFighterCollision(Asteroid* astroid, Fighter* fighter) :
			Message(ASTROID_FIGHTER_COLLISION), astroid_(astroid), fighter_(
					fighter) {
	}

	Asteroid* astroid_;
	Fighter* fighter_;
};

struct FighterIsShooting: Message {
	FighterIsShooting(Fighter* fighter, Vector2D bulletPosition,
			Vector2D bulletVelocity) :
			Message(FIGHTER_SHOOT), fighter_(fighter), bulletPosition_(
					bulletPosition), bulletVelocity_(bulletVelocity) {
	}

	Fighter* fighter_;
	Vector2D bulletPosition_;
	Vector2D bulletVelocity_;
};

struct GoDownBar : Message {
	GoDownBar(Fighter* fighter, int shotsRealized, int maxShots) :
		Message(BAR_SHOOT), fighter_(fighter), shotsRealized_(
			shotsRealized), maxShots_(maxShots) {
	}

	Fighter* fighter_;
	int shotsRealized_;
	int maxShots_;
};

struct GoDownLifeBar : Message {
	GoDownLifeBar(Fighter* fighter) :
		Message(BAR_LIFE), fighter_(fighter) {
	}

	Fighter* fighter_;
};

struct GoUpLifeBar : Message {
	GoUpLifeBar(Fighter* fighter) :
		Message(UPLIFE), fighter_(fighter) {
	}

	Fighter* fighter_;
};

struct noMoreAsteroids : Message {
	noMoreAsteroids(Fighter* fighter) :
		Message(NO_MORE_ATROIDS), fighter_(fighter) {
	}

	Fighter* fighter_;
};

#endif /* MESSAGES_H_ */
