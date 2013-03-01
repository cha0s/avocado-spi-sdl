#include "main/avocado-global.h"

#include "SdlCounter.h"

#include "SDL/SDL.h"

namespace avo {

AbstractFactory<SdlCounter> *SdlCounter::factory = new AbstractFactory<SdlCounter>();

SdlCounter::SdlCounter()
	: Counter()
{
	setCurrent(SDL_GetTicks());
}

SdlCounter::~SdlCounter() {

}

double SdlCounter::current() {
	return SDL_GetTicks();
}

}
