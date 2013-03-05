#include "core/avocado-global.h"

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

int keyCodeMap(SDLKey keyCode) {

	int mappedKeyCode;
	const std::map<std::string, int> &KeyCodes = Window::Event::KeyCodes();

	switch (keyCode) {

	case SDLK_a: mappedKeyCode = KeyCodes.at("A"); break;
	case SDLK_b: mappedKeyCode = KeyCodes.at("B"); break;
	case SDLK_c: mappedKeyCode = KeyCodes.at("C"); break;
	case SDLK_d: mappedKeyCode = KeyCodes.at("D"); break;
	case SDLK_e: mappedKeyCode = KeyCodes.at("E"); break;
	case SDLK_f: mappedKeyCode = KeyCodes.at("F"); break;
	case SDLK_g: mappedKeyCode = KeyCodes.at("G"); break;
	case SDLK_h: mappedKeyCode = KeyCodes.at("H"); break;
	case SDLK_i: mappedKeyCode = KeyCodes.at("I"); break;
	case SDLK_j: mappedKeyCode = KeyCodes.at("J"); break;
	case SDLK_k: mappedKeyCode = KeyCodes.at("K"); break;
	case SDLK_l: mappedKeyCode = KeyCodes.at("L"); break;
	case SDLK_m: mappedKeyCode = KeyCodes.at("M"); break;
	case SDLK_n: mappedKeyCode = KeyCodes.at("N"); break;
	case SDLK_o: mappedKeyCode = KeyCodes.at("O"); break;
	case SDLK_p: mappedKeyCode = KeyCodes.at("P"); break;
	case SDLK_q: mappedKeyCode = KeyCodes.at("Q"); break;
	case SDLK_r: mappedKeyCode = KeyCodes.at("R"); break;
	case SDLK_s: mappedKeyCode = KeyCodes.at("S"); break;
	case SDLK_t: mappedKeyCode = KeyCodes.at("T"); break;
	case SDLK_u: mappedKeyCode = KeyCodes.at("U"); break;
	case SDLK_v: mappedKeyCode = KeyCodes.at("V"); break;
	case SDLK_w: mappedKeyCode = KeyCodes.at("W"); break;
	case SDLK_x: mappedKeyCode = KeyCodes.at("X"); break;
	case SDLK_y: mappedKeyCode = KeyCodes.at("Y"); break;
	case SDLK_z: mappedKeyCode = KeyCodes.at("Z"); break;
	case SDLK_0: mappedKeyCode = KeyCodes.at("0"); break;
	case SDLK_1: mappedKeyCode = KeyCodes.at("1"); break;
	case SDLK_2: mappedKeyCode = KeyCodes.at("2"); break;
	case SDLK_3: mappedKeyCode = KeyCodes.at("3"); break;
	case SDLK_4: mappedKeyCode = KeyCodes.at("4"); break;
	case SDLK_5: mappedKeyCode = KeyCodes.at("5"); break;
	case SDLK_6: mappedKeyCode = KeyCodes.at("6"); break;
	case SDLK_7: mappedKeyCode = KeyCodes.at("7"); break;
	case SDLK_8: mappedKeyCode = KeyCodes.at("8"); break;
	case SDLK_9: mappedKeyCode = KeyCodes.at("9"); break;
	case SDLK_ESCAPE: mappedKeyCode = KeyCodes.at("Escape"); break;
	case SDLK_LCTRL: mappedKeyCode = KeyCodes.at("ControlLeft"); break;
	case SDLK_LSHIFT: mappedKeyCode = KeyCodes.at("ShiftLeft"); break;
	case SDLK_LALT: mappedKeyCode = KeyCodes.at("AltLeft"); break;
	case SDLK_LSUPER: mappedKeyCode = KeyCodes.at("SystemLeft"); break;
	case SDLK_RCTRL: mappedKeyCode = KeyCodes.at("ControlRight"); break;
	case SDLK_RSHIFT: mappedKeyCode = KeyCodes.at("ShiftRight"); break;
	case SDLK_RALT: mappedKeyCode = KeyCodes.at("AltRight"); break;
	case SDLK_RSUPER: mappedKeyCode = KeyCodes.at("SystemRight"); break;
	case SDLK_MENU: mappedKeyCode = KeyCodes.at("Menu"); break;
	case SDLK_LEFTBRACKET: mappedKeyCode = KeyCodes.at("BracketLeft"); break;
	case SDLK_RIGHTBRACKET: mappedKeyCode = KeyCodes.at("BracketRight"); break;
	case SDLK_SEMICOLON: mappedKeyCode = KeyCodes.at("Semicolon"); break;
	case SDLK_COLON: mappedKeyCode = KeyCodes.at("Colon"); break;
	case SDLK_COMMA: mappedKeyCode = KeyCodes.at("Comma"); break;
	case SDLK_PERIOD: mappedKeyCode = KeyCodes.at("Period"); break;
	case SDLK_QUOTE: mappedKeyCode = KeyCodes.at("QuotationMark"); break;
	case SDLK_SLASH: mappedKeyCode = KeyCodes.at("Slash"); break;
	case SDLK_BACKSLASH: mappedKeyCode = KeyCodes.at("Backslash"); break;
	case SDLK_BACKQUOTE: mappedKeyCode = KeyCodes.at("Backtick"); break;
	case SDLK_EQUALS: mappedKeyCode = KeyCodes.at("EqualsSign"); break;
	case SDLK_MINUS: mappedKeyCode = KeyCodes.at("Dash"); break;
	case SDLK_SPACE: mappedKeyCode = KeyCodes.at("Space"); break;
	case SDLK_RETURN: mappedKeyCode = KeyCodes.at("Enter"); break;
	case SDLK_BACKSPACE: mappedKeyCode = KeyCodes.at("Backspace"); break;
	case SDLK_TAB: mappedKeyCode = KeyCodes.at("Tab"); break;
	case SDLK_PAGEUP: mappedKeyCode = KeyCodes.at("PageUp"); break;
	case SDLK_PAGEDOWN: mappedKeyCode = KeyCodes.at("PageDown"); break;
	case SDLK_END: mappedKeyCode = KeyCodes.at("End"); break;
	case SDLK_HOME: mappedKeyCode = KeyCodes.at("Home"); break;
	case SDLK_INSERT: mappedKeyCode = KeyCodes.at("Insert"); break;
	case SDLK_DELETE: mappedKeyCode = KeyCodes.at("Delete"); break;
	case SDLK_PLUS: mappedKeyCode = KeyCodes.at("Plus"); break;
	case SDLK_ASTERISK: mappedKeyCode = KeyCodes.at("Asterisk"); break;
	case SDLK_LEFT: mappedKeyCode = KeyCodes.at("ArrowLeft"); break;
	case SDLK_RIGHT: mappedKeyCode = KeyCodes.at("ArrowRight"); break;
	case SDLK_UP: mappedKeyCode = KeyCodes.at("ArrowUp"); break;
	case SDLK_DOWN: mappedKeyCode = KeyCodes.at("ArrowDown"); break;
	case SDLK_F1: mappedKeyCode = KeyCodes.at("F1"); break;
	case SDLK_F2: mappedKeyCode = KeyCodes.at("F2"); break;
	case SDLK_F3: mappedKeyCode = KeyCodes.at("F3"); break;
	case SDLK_F4: mappedKeyCode = KeyCodes.at("F4"); break;
	case SDLK_F5: mappedKeyCode = KeyCodes.at("F5"); break;
	case SDLK_F6: mappedKeyCode = KeyCodes.at("F6"); break;
	case SDLK_F7: mappedKeyCode = KeyCodes.at("F7"); break;
	case SDLK_F8: mappedKeyCode = KeyCodes.at("F8"); break;
	case SDLK_F9: mappedKeyCode = KeyCodes.at("F9"); break;
	case SDLK_F10: mappedKeyCode = KeyCodes.at("F10"); break;
	case SDLK_F11: mappedKeyCode = KeyCodes.at("F11"); break;
	case SDLK_F12: mappedKeyCode = KeyCodes.at("F12"); break;
	case SDLK_F13: mappedKeyCode = KeyCodes.at("F13"); break;
	case SDLK_F14: mappedKeyCode = KeyCodes.at("F14"); break;
	case SDLK_F15: mappedKeyCode = KeyCodes.at("F15"); break;
	case SDLK_PAUSE: mappedKeyCode = KeyCodes.at("Pause"); break;
	case SDLK_KP0: mappedKeyCode = KeyCodes.at("0"); break;
	case SDLK_KP1: mappedKeyCode = KeyCodes.at("1"); break;
	case SDLK_KP2: mappedKeyCode = KeyCodes.at("2"); break;
	case SDLK_KP3: mappedKeyCode = KeyCodes.at("3"); break;
	case SDLK_KP4: mappedKeyCode = KeyCodes.at("4"); break;
	case SDLK_KP5: mappedKeyCode = KeyCodes.at("5"); break;
	case SDLK_KP6: mappedKeyCode = KeyCodes.at("6"); break;
	case SDLK_KP7: mappedKeyCode = KeyCodes.at("7"); break;
	case SDLK_KP8: mappedKeyCode = KeyCodes.at("8"); break;
	case SDLK_KP9: mappedKeyCode = KeyCodes.at("9"); break;
	case SDLK_KP_PERIOD: mappedKeyCode = KeyCodes.at("Period"); break;
	case SDLK_KP_DIVIDE: mappedKeyCode = KeyCodes.at("Slash"); break;
	case SDLK_KP_MULTIPLY: mappedKeyCode = KeyCodes.at("Asterisk"); break;
	case SDLK_KP_MINUS: mappedKeyCode = KeyCodes.at("Dash"); break;
	case SDLK_KP_PLUS: mappedKeyCode = KeyCodes.at("Plus"); break;
	case SDLK_KP_ENTER: mappedKeyCode = KeyCodes.at("Enter"); break;
	case SDLK_KP_EQUALS: mappedKeyCode = KeyCodes.at("EqualsSign"); break;
	default: break;
	}

	return mappedKeyCode;
}

int mouseButtonMap(Uint8 button) {

	int mappedButton;
	const std::map<std::string, int> &MouseButtons = Window::Event::MouseButtons();

	switch (button) {
		case SDL_BUTTON_LEFT: mappedButton = MouseButtons.at("ButtonLeft"); break;
		case SDL_BUTTON_MIDDLE: mappedButton = MouseButtons.at("ButtonMiddle"); break;
		case SDL_BUTTON_RIGHT: mappedButton = MouseButtons.at("ButtonRight"); break;
		case SDL_BUTTON_WHEELUP: mappedButton = 0; break;
		case SDL_BUTTON_WHEELDOWN: mappedButton = 0; break;
		default: break;
	}

	return mappedButton;
}

Window::Event SdlWindow::pollEvents() {

	Event event;
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {

		switch (sdlEvent.type) {

		case SDL_KEYDOWN: {

			Event::KeyDown keyDown = {keyCodeMap(sdlEvent.key.keysym.sym)};
			event.keyDown.push_back(keyDown);

			break;
		}

		case SDL_KEYUP: {

			Event::KeyUp keyUp = {keyCodeMap(sdlEvent.key.keysym.sym)};
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

			int code = mouseButtonMap(sdlEvent.button.button);
			if (-1 != code) {

				Event::MouseButtonDown mouseDown = {
					sdlEvent.button.x,
					sdlEvent.button.y,
					code
				};
				event.mouseButtonDown.push_back(mouseDown);
			}
			else {

				Event::MouseWheelMove mouseWheelMove = {
					sdlEvent.button.button == SDL_BUTTON_WHEELUP ? 1 : -1,
				};
				event.mouseWheelMove.push_back(mouseWheelMove);
			}

			break;
		}

		case SDL_MOUSEBUTTONUP: {

			Event::MouseButtonUp mouseUp = {
				sdlEvent.button.x,
				sdlEvent.button.y,
				mouseButtonMap(sdlEvent.button.button)
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

