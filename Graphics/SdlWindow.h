#ifndef AVOCADO_SDLWINDOW_H
#define AVOCADO_SDLWINDOW_H

#include "core/avocado-global.h"

#include <string>

#include "core/Graphics/Window.h"

#include "SdlCanvas.h"
#include "SdlImage.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * Represents the screen buffers and operations.
 *
 * @ingroup SDL
 */
class SdlWindow : public Window {

public:

	SdlWindow();
	~SdlWindow();

	Event pollEvents();

	void render(Canvas *working, int x, int y, int w, int h);

	void render(Image *working, int x, int y, int w, int h);

	void setFlags(WindowFlags flags = Flags_Default);

	void setSize(int width, int height);

	void setMouseVisibility(bool visible);

	void setWindowTitle(const std::string &window, const std::string &iconified = "");

	static AbstractFactory<SdlWindow> *factory;

private:

	void set();

	SdlCanvas *canvas;
};

/**
 * @ingroup Manufacturing
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlWindow> : public AbstractFactory<Window> {

public:

	virtual ~AbstractFactory<SdlWindow>() {}

	SdlWindow *create() {
		return new SdlWindow();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLWINDOW_H
