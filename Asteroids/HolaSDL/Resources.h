#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "Texture.h"
#include "Font.h"
#include "Music.h"
#include "SoundEffect.h"
#include "checkML.h"
#include <vector>
#include <tuple>

class SDLGame;
class Resources {
public:
	// in this part we define the enums for the resources, and the
	// corresponding data to be used to create them. The enums are simple
	// used to make access readable ...

	// Images -- each image file is loaded as an instance of Texture
	//
	enum ImageId {
		Blank,
		TennisBall,
		KeyBoardIcon,
		MouseIcon,
		AIIcon,
		SpaceShips,
		Airplanes,
		Star,
		Ship, Ship2, Ship3, Ship4, Ship5, Ship6,
		Laser,
		Background,
		Asteroid,
		HUD,
		Shoot,
		Life,
		HUD2,
		Victory,
		Loose,
		Champ,
		Feather,
		Bomb,
		Thwomp,
		Bill,
		UP
	};

	// Text Messages - each is loaded as an instance of a texture
	enum TextId {
		HelloWorld, PresAnyKey, GameOver
	};

	// Fonts -- they are pair of filename and size, each is loaded as
	// an instance of Font
	//
	enum FontId {
		ARIAL16, ARIAL24, NESChimera16, NESChimera24, CaptureIt16, CaptureIt24
	};


	// Music -- each file is loaded as an instance of Music
	//
	enum MusicId {
		BackgroundMusic
	};


	// Sound Effects -- each file is loaded as an instance of SoundEffect
	//
	enum SoundEffectId {
		Death, Explosion, Over, Shoott, Start
	};

private:

	struct TextMsgInfo {
		std::string text;
		SDL_Color color;
		FontId fontId;
	};

	struct FontInfo {
		std::string fileName;
		int size;
	};

	static std::vector<std::string> imageFiles_; // initialized in .cpp
	static std::vector<TextMsgInfo> textMsgs_; // initialized in .cpp
	static std::vector<FontInfo> fontFiles_; // initialized in .cpp
	static std::vector<std::string> musicFiles_; // initialized in .cpp
	static std::vector<std::string> soundEffectFiles_; // initialized in .cpp


public:

	Resources(SDLGame* game);
	virtual ~Resources();


	Texture* getImageTexture(ImageId i) const;
	Texture* getTextTexture(TextId i) const;
	Font* getFont(FontId i) const;
	Music* getMusic(MusicId i) const;
	SoundEffect* getSoundEffect(SoundEffectId i) const;

private:
	void setImageTextures(std::vector<std::string> textures);
	void setTextTextures(std::vector<TextMsgInfo> texts);
	void setFonts(std::vector<FontInfo> fonts);
	void setMusic(std::vector<std::string> music);
	void setSoundEffects(std::vector<std::string> soundEffects);

	void closeImageTextures();
	void closeTextTextures();
	void closeFonts();
	void closeMusic();
	void closeSoundEffects();

	SDLGame* game_;

	int numOfImageTextures_;
	Texture** imageTextures_;

	int numOfTextTextures_;
	Texture** textTextures_;

	int numOfFonts_;
	Font** fonts_;

	int numOfMusic_;
	Music** music_;

	int numOfSoundEffects_;
	SoundEffect** soundEffects_;
};

#endif /* RESOURCES_H_ */
