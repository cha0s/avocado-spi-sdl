#ifndef AVOCADO_SDLSPRITE_H
#define AVOCADO_SDLSPRITE_H

#include "core/avocado-global.h"

#include "SDL/SDL.h"

#include "core/Graphics/Canvas.h"
#include "core/Graphics/Sprite.h"
#include "core/Graphics/Window.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * SDL Sprite SPI implementation (SPII).
 *
 * @ingroup SDL
 */
class SdlSprite : public Sprite {

public:

	SdlSprite();

	void renderTo(Canvas *destination) const;

	void renderTo(Window *destination) const;

	void renderTo(SDL_Surface *destination, bool copyPixels) const;

	void setAlpha(double alpha);

	void setBlendMode(GraphicsService::BlendMode blendMode);

	void setPosition(int x, int y);

	void setRotation(double angle, int orientX, int orientY);

	void setScale(double factorX, double factorY);

	void setSourceRectangle(int x, int y, int w, int h);

	static AbstractFactory<SdlSprite> *factory;

	/**
	 * Per pixel alpha blending.
	 */
	static inline unsigned int blendPixel(unsigned int src, unsigned int dst, double alpha = 1) {

		unsigned char *sc = reinterpret_cast<unsigned char *>(&src);
		if (0 == sc[3]) return dst;

		unsigned char *dc = reinterpret_cast<unsigned char *>(&dst);

		double pAlpha = (sc[3] / 255.0) * alpha;
		dc[0] = sc[0] * pAlpha + dc[0] * (1.0 - pAlpha);
		dc[1] = sc[1] * pAlpha + dc[1] * (1.0 - pAlpha);
		dc[2] = sc[2] * pAlpha + dc[2] * (1.0 - pAlpha);

		// ???
		dc[3] = pAlpha;

		return dst;
	}

private:

	double alpha;

	GraphicsService::BlendMode blendMode;

	int x;
	int y;

	double angle;
	int orientX;
	int orientY;

	double factorX;
	double factorY;

	int sourceX;
	int sourceY;
	int sourceW;
	int sourceH;

};

/**
 * @ingroup Manufacturing
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlSprite> : public AbstractFactory<Sprite> {

	virtual ~AbstractFactory<SdlSprite>() {}

	SdlSprite *create() {
		return new SdlSprite();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLSPRITE_H
