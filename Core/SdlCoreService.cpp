#include "main/avocado-global.h"

#include "SdlCoreService.h"

#include "SDL/SDL.h"

namespace avo {

AbstractFactory<SdlCoreService> *SdlCoreService::factory = new AbstractFactory<SdlCoreService>;

SdlCoreService::SdlCoreService() {
	SDL_Init(SDL_INIT_NOPARACHUTE);
}

SdlCoreService::~SdlCoreService() {
	close();
}

void SdlCoreService::close() {
	CoreService::close();

	SDL_Quit();
}

}
