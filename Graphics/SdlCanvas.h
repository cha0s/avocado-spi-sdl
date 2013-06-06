#ifndef AVOCADO_SDLCANVAS_H
#define AVOCADO_SDLCANVAS_H

#include "core/avocado-global.h"

#include "SDL/SDL.h"

#include "core/Graphics/Canvas.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * SDL image SPI implementation (SPII). The SPII uses SDL_Surface to implement
 * the image operations.
 *
 * @ingroup Resources
 * @ingroup SDL
 */
class SdlCanvas : public Canvas {

public:

	friend class SdlWindow;

	/**
	 * Build a NULL SDL_Surface.
	 */
	SdlCanvas();

	/**
	 * Load an SDL_Surface from a filename.
	 */
	SdlCanvas(const boost::filesystem::path &uri);

	/**
	 * Build an SDL_Surface to given width/height specifcations.
	 */
	SdlCanvas(int width, int height);

	/**
	 * Destroy SDL_Surface.
	 */
	~SdlCanvas();

	void drawCircle(int x, int y, int radius, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void drawFilledBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void drawLineBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode);

	void fill(int r, int g, int b, double a);

	int height() const;

	bool isValid() const { return width() != 0 && height() != 0; }

	unsigned int pixelAt(int x, int y) const;

	void saveToFile(const boost::filesystem::path &filename);

	void setPixelAt(int x, int y, unsigned int pixel);

	int width() const;

	SDL_Surface *surface();

	static AbstractFactory<SdlCanvas> *factory;

private:

	mutable SDL_Surface *_surface;

};

/**
 * @ingroup Manufacturing
 * @ingroup Resources
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlCanvas> : public AbstractFactory<Canvas> {

	virtual ~AbstractFactory<SdlCanvas>() {}

	SdlCanvas *create(const boost::filesystem::path &uri) {
		return new SdlCanvas(uri);
	}

	SdlCanvas *create(int width, int height) {
		return new SdlCanvas(width, height);
	}

	SdlCanvas *create() {
		return new SdlCanvas();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLCANVAS_H
