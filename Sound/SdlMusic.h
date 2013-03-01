#ifndef AVOCADO_SDLMUSIC_H
#define AVOCADO_SDLMUSIC_H

#include "main/avocado-global.h"

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "SPI/Abstract/Sound/Music.h"

namespace avo {

/**
 * @addtogroup Sound
 * @{
 */

class SdlMusic;

/**
 * @ingroup Resources
 * @ingroup SDL
 */
class SdlMusic : public Music {

public:

	/**
	 * Create an empty music resource.
	 */
	SdlMusic();

	/**
	 * Load Mix_Music from a URI.
	 */
	SdlMusic(const boost::filesystem::path &uri);

	/**
	 * Release Mix_Music.
	 */
	~SdlMusic();

	void fadeIn(int loops = LoopForever, int ms = 3000, int position = 0);

	void fadeOut(int ms = 3000);

	int isPlaying();

	int play(int loops = LoopForever);

	void setVolume(int volume);

	void stop();

	int volume();

	static AbstractFactory<SdlMusic> *factory;

private:

	Mix_Music *music;

};

/**
 * @ingroup Manufacturing
 * @ingroup Resources
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlMusic> : public AbstractFactory<Music> {

public:

	virtual ~AbstractFactory<SdlMusic>() {}

	SdlMusic *create() { return new SdlMusic(); }
	SdlMusic *create(const boost::filesystem::path &uri) { return new SdlMusic(uri); }

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLMUSIC_H
