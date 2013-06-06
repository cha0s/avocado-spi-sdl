#include "core/avocado-global.h"

#include "SdlSprite.h"

#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"

#include "SdlCanvas.h"
#include "SdlImage.h"
#include "SdlWindow.h"

namespace avo {

AbstractFactory<SdlSprite> *SdlSprite::factory = new AbstractFactory<SdlSprite>;

SdlSprite::SdlSprite()
	: Sprite()
	, alpha(1)
	, blendMode(GraphicsService::BlendMode_Blend)
	, x(0)
	, y(0)
	, angle(0)
	, orientX(0)
	, orientY(0)
	, factorX(1)
	, factorY(1)
	, sourceX(0)
	, sourceY(0)
	, sourceW(0)
	, sourceH(0)
{
}

void SdlSprite::renderTo(Canvas *destination) const {
	renderTo(Canvas::superCast<SdlCanvas>(destination)->surface(), false);
}

void SdlSprite::renderTo(Window *destination) const {

	SDL_Surface *windowSurface = Window::superCast<SdlWindow>(
		destination
	)->canvas()->surface();

	renderTo(windowSurface, true);
	SDL_UpdateRect(windowSurface, 0, 0, 0, 0);
}

void SdlSprite::renderTo(SDL_Surface *destination, bool copyPixels) const {
	if (NULL == canvas() && NULL == image()) return;

	int sw = sourceW;
	int sh = sourceH;

	// If src_rect doesn't have a valid width or height, set them
	// to this Canvas object's dimensions.
	if (0 == sw || 0 == sh) {
		sw = canvas() ? canvas()->width() : image()->width();
		sh = canvas() ? canvas()->height() : image()->height();
	}

	// SDL's blitting sucks ass. I need to fucking learn OpenGL already! Damn
	// it!!!
	if (0 == alpha && GraphicsService::BlendMode_Blend == blendMode) {

		// Woohoo!
		return;
	}
	else {

		int sx = sourceX;
		int sy = sourceY;
		SDL_Surface *surface = NULL;

		if (image()) {
			surface = Image::superCast<SdlImage>(image())->surface();
		}
		else if (canvas()) {
			surface = Canvas::superCast<SdlImage>(canvas())->surface();
		}

		int sIdx = sy * surface->w + sx;

		if (sy < 0) {
			sh += sy;
			sIdx -= sy * surface->w;
			sy = 0;
		}
		if (sx < 0) {
			sw += sx;
			sIdx -= sx;
			sx = 0;
		}

		if (sx + sw > surface->w) {
			sw = surface->w - sx;
		}
		if (sy + sh > surface->h) {
			sh = surface->h - sy;
		}

		int dx = x;
		int dy = y;
		int dw = destination->w;
		int dh = destination->h;

		if (dy < 0) {
			sh += dy;
			sIdx -= dy * surface->w;
			dy = 0;
		}
		if (dx < 0) {
			sw += dx;
			sIdx -= dx;
			dx = 0;
		}

		if (dx + sw > dw) {
			sw = dw - dx;
		}
		if (dy + sh > dh) {
			sh = dh - dy;
		}

		int dIdx = dy * destination->w + dx;

		// 32-bit implied; we ain't fucking around with no bullshit!
		SDL_LockSurface(surface);
		SDL_LockSurface(destination);

		// Take addresses of the first pixel of the source and destination.
		unsigned int *src = (unsigned int *)surface->pixels, *dst = (unsigned int *)destination->pixels;
		unsigned char *sc;

		src += sIdx;
		dst += dIdx;

		// For each pixel from the source image, make it a
		// 2 x 2 block in the destination.
		for (int y = 0; y < sh; ++y) {
			for (int x = 0; x < sw; ++x) {

				sc = reinterpret_cast<unsigned char *>(src);

				int dstColor;
				if (copyPixels) {
					*dst = *src;
				}
				else if (GraphicsService::BlendMode_Replace == blendMode || (255 == alpha && 255 == sc[3])) {
					dstColor = 255 << 24 | 255 << 16;
					*dst = blendPixel(*src, dstColor, alpha);
				}
				else {
					dstColor = *dst;
					*dst = blendPixel(*src, dstColor, alpha);
				}

				src++;
				dst++;
			}
			dst -= sw;
			dst += destination->w;
			src -= sw;
			src += surface->w;
		}

		SDL_UnlockSurface(destination);
		SDL_UnlockSurface(surface);
	}
}

void SdlSprite::setAlpha(double alpha) {
	this->alpha = alpha;
}

void SdlSprite::setBlendMode(GraphicsService::BlendMode blendMode) {
	this->blendMode = blendMode;
}

void SdlSprite::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

void SdlSprite::setRotation(double angle, int orientX, int orientY) {
	this->angle = angle;
	this->orientX = orientX;
	this->orientY = orientY;
}

void SdlSprite::setScale(double factorX, double factorY) {
	this->factorX = factorX;
	this->factorY = factorY;
}

void SdlSprite::setSourceRectangle(int x, int y, int w, int h) {
	this->sourceX = x;
	this->sourceY = y;
	this->sourceW = w;
	this->sourceH = h;
}

}

