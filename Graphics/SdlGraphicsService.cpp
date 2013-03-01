#include "main/avocado-global.h"

#include "SdlGraphicsService.h"

#include "SdlImage.h"
#include "SdlWindow.h"

namespace avo {

AbstractFactory<SdlGraphicsService> *SdlGraphicsService::factory = new AbstractFactory<SdlGraphicsService>;

SdlGraphicsService::SdlGraphicsService() {

	Image::factoryManager.setInstance(SdlImage::factory);
	Window::factoryManager.setInstance(SdlWindow::factory);

	// Center the window.
	SDL_putenv(const_cast<char *>("SDL_VIDEO_CENTERED=center"));

	// If any video driver is specified in the environment, save it since
	// we're going to set 'dummy'.
	const char *currentDriver = SDL_getenv(const_cast<char *>("SDL_VIDEODRIVER"));
	if (currentDriver) {

		// (Safely) copy the new driver into a C string for SDL_putenv().
		std::string driver = "AVOCADO_SDL_VIDEODRIVER=";
		driver += currentDriver;
		char *driverArray = new char[256];
		strncpy(driverArray, driver.c_str(), 255);
		driverArray[255] = 0;
		SDL_putenv(driverArray);
	}
	SDL_putenv(const_cast<char *>("AVOCADO_SDL_VIDEORESTORE=1"));
	SDL_putenv(const_cast<char *>("SDL_VIDEODRIVER=dummy"));

	// Initialize a 'dummy' video mode, so we can create SDL surfaces before
	// we actually set a window.
	SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	SDL_SetVideoMode(1, 1, 32, 0);

	// Initialize any joysticks/gamepads.
	if ((numJoysticks = SDL_NumJoysticks()) > 0) {
	    SDL_JoystickEventState(SDL_ENABLE);
	    joystick = new SDL_Joystick *[numJoysticks];
	    for (int i = 0; i < numJoysticks; i++) {
		    joystick[i] = SDL_JoystickOpen(i);
	    }
	}
}

SdlGraphicsService::~SdlGraphicsService() {
	SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
}

void SdlGraphicsService::close() {
	GraphicsService::close();
}

GraphicsService::SpecialKeyCodes SdlGraphicsService::specialKeyCodes() {

	SpecialKeyCodes keyMap;

	keyMap.UpArrow = SDLK_UP;
	keyMap.RightArrow = SDLK_RIGHT;
	keyMap.DownArrow = SDLK_DOWN;
	keyMap.LeftArrow = SDLK_LEFT;

	return keyMap;
}

}
