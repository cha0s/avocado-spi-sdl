#ifndef AVOCADO_SDLIMAGE_H
#define AVOCADO_SDLIMAGE_H

#include "core/avocado-global.h"

#include "SDL/SDL.h"

#include "core/Graphics/Image.h"

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
class SdlImage : public Image {

public:

	/** SdlWindow needs access to SDL_Surface. */
	friend class SdlWindow;

	/**
	 * Build a NULL SDL_Surface.
	 */
	SdlImage();

	/**
	 * Load an SDL_Surface from a filename.
	 */
	SdlImage(const boost::filesystem::path &uri);

	/**
	 * Build an SDL_Surface to given width/height specifcations.
	 */
	SdlImage(int width, int height);

	/**
	 * Destroy SDL_Surface.
	 */
	~SdlImage();

	void drawCircle(int x, int y, int radius, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void drawFilledBox(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void drawLineBox(int x, int y, int w, int h, int r, int g, int b, int a = 255, DrawMode drawMode = DrawMode_Blend);

	void fill(int r, int g, int b, int a = 255);

	int height() const;

	bool isValid() const { return width() != 0 && height() != 0; }

	unsigned int pixelAt(int x, int y) const;

	void render(int x, int y, Image *destination, int alpha = 255, DrawMode mode = DrawMode_Blend, int sx = 0, int sy = 0, int sw = 0, int sh = 0) const AVOCADO_ENSURE_STACK_ALIGNED_FOR_SSE;

	void saveToFile(const boost::filesystem::path &filename);

	void setPixelAt(int x, int y, unsigned int pixel);

	int width() const;

	/**
	 * Per pixel alpha blending.
	 */
	static inline unsigned int blendPixel(unsigned int src, unsigned int dst, int alpha = 255) {

		unsigned char *sc = reinterpret_cast<unsigned char *>(&src);
		if (0 == sc[3]) return dst;

		unsigned char *dc = reinterpret_cast<unsigned char *>(&dst);

		int pAlpha = sc[3] * (alpha / 255.0);
		dc[0] = (sc[0] * pAlpha + dc[0] * (255 - pAlpha)) / 255;
		dc[1] = (sc[1] * pAlpha + dc[1] * (255 - pAlpha)) / 255;
		dc[2] = (sc[2] * pAlpha + dc[2] * (255 - pAlpha)) / 255;

		// ???
		dc[3] = pAlpha;

		return dst;
	}

	static AbstractFactory<SdlImage> *factory;

private:

	SDL_Surface *surface;

};

/**
 * @ingroup Manufacturing
 * @ingroup Resources
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlImage> : public AbstractFactory<Image> {

	virtual ~AbstractFactory<SdlImage>() {}

	SdlImage *create(const boost::filesystem::path &uri) {
		return new SdlImage(uri);
	}

	SdlImage *create(int width, int height) {
		return new SdlImage(width, height);
	}

	SdlImage *create() {
		return new SdlImage();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLIMAGE_H
