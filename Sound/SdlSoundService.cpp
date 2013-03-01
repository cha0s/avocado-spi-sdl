#include "main/avocado-global.h"

#include "SdlSoundService.h"

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

#include "SdlMusic.h"
#include "SdlSample.h"

namespace avo {

AbstractFactory<SdlSoundService> *SdlSoundService::factory = new AbstractFactory<SdlSoundService>;

SdlSoundService::SdlSoundService() {

	SDL_InitSubSystem(SDL_INIT_AUDIO);

	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_AllocateChannels(16);

	Sample::factoryManager.setInstance(SdlSample::factory);
	Music::factoryManager.setInstance(SdlMusic::factory);
}

SdlSoundService::~SdlSoundService() {

	Mix_CloseAudio();

	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void SdlSoundService::close() {
	SoundService::close();
}

}
