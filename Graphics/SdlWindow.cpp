#include "main/avocado-global.h"

#include "SdlWindow.h"

using namespace std;

const double JoystickMagnitude = 32767;

namespace avo {

AbstractFactory<SdlWindow> *SdlWindow::factory = new AbstractFactory<SdlWindow>();

SdlWindow::SdlWindow()
	: Window()
	, image(new SdlImage())
{
}

SdlWindow::~SdlWindow() {

	// SDL will free the surface automatically.
	image->surface = NULL;

	delete image;
}

Window::Event SdlWindow::pollEvents() {

	Event event;
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {

		switch (sdlEvent.type) {

		case SDL_KEYDOWN: {

			Event::KeyDown keyDown = {sdlEvent.key.keysym.sym};
			event.keyDown.push_back(keyDown);

			break;
		}

		case SDL_KEYUP: {

			Event::KeyUp keyUp = {sdlEvent.key.keysym.sym};
			event.keyUp.push_back(keyUp);

			break;
		}

		case SDL_JOYAXISMOTION: {

			Event::JoyAxis joyAxis = {
				sdlEvent.jaxis.which,
				sdlEvent.jaxis.axis,
				sdlEvent.jaxis.value / JoystickMagnitude
			};

			deque<Event::JoyAxis>::iterator i = find(
				event.joyAxis.begin(),
				event.joyAxis.end(),
				joyAxis
			);

			if (event.joyAxis.end() == i) {
				event.joyAxis.push_back(joyAxis);
			}
			else {
				i->value = joyAxis.value;
			}

			break;
		}

		case SDL_JOYBUTTONDOWN: {

			Event::JoyButtonDown joyButtonDown = {
				sdlEvent.jbutton.which,
				sdlEvent.jbutton.button
			};

			deque<Event::JoyButtonDown>::iterator i = find(
				event.joyButtonDown.begin(),
				event.joyButtonDown.end(),
				joyButtonDown
			);

			if (event.joyButtonDown.end() == i) {
				event.joyButtonDown.push_back(joyButtonDown);
			}

			break;
		}

		case SDL_JOYBUTTONUP: {

			Event::JoyButtonUp joyButtonUp = {
				sdlEvent.jbutton.which,
				sdlEvent.jbutton.button
			};

			deque<Event::JoyButtonUp>::iterator i = find(
				event.joyButtonUp.begin(),
				event.joyButtonUp.end(),
				joyButtonUp
			);

			if (event.joyButtonUp.end() == i) {
				event.joyButtonUp.push_back(joyButtonUp);
			}

			break;
		}

		case SDL_MOUSEBUTTONDOWN: {

			Event::MouseButtons button;
			switch (sdlEvent.button.button) {
				case SDL_BUTTON_LEFT: button = Event::LeftButton; break;
				case SDL_BUTTON_MIDDLE: button = Event::MiddleButton; break;
				case SDL_BUTTON_RIGHT: button = Event::RightButton; break;
				case SDL_BUTTON_WHEELUP: button = Event::WheelUp; break;
				case SDL_BUTTON_WHEELDOWN: button = Event::WheelDown; break;
			}
			Event::MouseButtonDown mouseDown = {
				sdlEvent.button.x,
				sdlEvent.button.y,
				button
			};
			event.mouseButtonDown.push_back(mouseDown);

			break;
		}

		case SDL_MOUSEBUTTONUP: {

			Event::MouseButtons button;
			switch (sdlEvent.button.button) {
				case SDL_BUTTON_LEFT: button = Event::LeftButton; break;
				case SDL_BUTTON_MIDDLE: button = Event::MiddleButton; break;
				case SDL_BUTTON_RIGHT: button = Event::RightButton; break;
				case SDL_BUTTON_WHEELUP: button = Event::WheelUp; break;
				case SDL_BUTTON_WHEELDOWN: button = Event::WheelDown; break;
			}
			Event::MouseButtonUp mouseUp = {
				sdlEvent.button.x,
				sdlEvent.button.y,
				button
			};
			event.mouseButtonUp.push_back(mouseUp);

			break;
		}

		case SDL_MOUSEMOTION: {

			Event::MouseMove mouseMove = {
				sdlEvent.motion.x,
				sdlEvent.motion.y
			};
			event.mouseMove.push_back(mouseMove);

			break;
		}

		case SDL_QUIT: {

			event.quit = true;
			break;
		}

		case SDL_VIDEORESIZE: {

			event.resize.width = sdlEvent.resize.w;
			event.resize.height = sdlEvent.resize.h;

			break;
		}

		default: {
			break;

		}

		}
	}

	return event;
}

void SdlWindow::render(Image *working, int x, int y, int w, int h) {

	SDL_Rect src = {x, y, w, h};
	SDL_Rect dst = {x, y, w, h};

	SDL_BlitSurface(
		Image::superCast<SdlImage>(working)->surface,
		&src,
		Image::superCast<SdlImage>(image)->surface,
		&dst
	);
	SDL_UpdateRect(image->surface, x, y, w, h);
}

void SdlWindow::set() {

	// We have to restore the video mode at least once, since we set dummy
	// during SPII initialization (to allow images to be created before we
	// get to this call).
	if (SDL_getenv(const_cast<char *>("AVOCADO_SDL_VIDEORESTORE"))) {
		SDL_QuitSubSystem(SDL_INIT_VIDEO);

		// Get the current driver, if any.
		const char *currentDriver = SDL_getenv(const_cast<char *>("AVOCADO_SDL_VIDEODRIVER"));
		if (currentDriver && "" != std::string(currentDriver)) {
			std::string driver = "SDL_VIDEODRIVER=";
			driver += currentDriver;

			// (Safely) copy the new driver into a C string for SDL_putenv().
			char *driverArray = new char[256];
			strncpy(driverArray, driver.c_str(), 255);
			driverArray[255] = 0;
			SDL_putenv(driverArray);
		}

		// Otherwise, let SDL decide which driver to use.
		else {
#ifdef __MINGW32__
			SDL_putenv(const_cast<char *>("SDL_VIDEODRIVER="));
#else
			unsetenv("SDL_VIDEODRIVER");
#endif
		}

		SDL_InitSubSystem(SDL_INIT_VIDEO);

		// We only want to restore the video driver once.
#ifdef __MINGW32__
		SDL_putenv(const_cast<char *>("AVOCADO_SDL_VIDEODRIVER="));
#else
		unsetenv("AVOCADO_SDL_VIDEODRIVER");
#endif

	}

	// Translate Window flags to SDL flags.
	int sdlFlags = 0;
	if (flags() & Flags_Fullscreen) sdlFlags |= SDL_FULLSCREEN;

	// Access the image internals to directly set the screen buffer.
	image->surface = SDL_SetVideoMode(width(), height(), 32, sdlFlags);
}

void SdlWindow::setFlags(WindowFlags flags) {
	Window::setFlags(flags);

	set();
}

void SdlWindow::setSize(int width, int height) {
	Window::setSize(width, height);

	set();
}

void SdlWindow::setMouseVisibility(bool visible) {
	SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}

void SdlWindow::setWindowTitle(const std::string &window, const std::string &iconified) {

	SDL_WM_SetCaption(
		window.c_str(),
		(iconified == "" ? window : iconified).c_str()
	);
}

}

