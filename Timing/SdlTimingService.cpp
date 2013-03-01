#include "main/avocado-global.h"

#include "SdlTimingService.h"

#include "SdlCounter.h"

namespace avo {

AbstractFactory<SdlTimingService> *SdlTimingService::factory = new AbstractFactory<SdlTimingService>;

SdlTimingService::SdlTimingService() {

	Counter::factoryManager.setInstance(SdlCounter::factory);

	SDL_InitSubSystem(SDL_INIT_TIMER);
}

SdlTimingService::~SdlTimingService() {
}

void SdlTimingService::sleep(int ms) {
	SDL_Delay(ms);
}

void SdlTimingService::close() {
	TimingService::close();

	SDL_QuitSubSystem(SDL_INIT_TIMER);
}

}
