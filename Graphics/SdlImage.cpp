#include "core/avocado-global.h"

#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"

#include "SdlCanvas.h"
#include "SdlImage.h"

namespace avo {

AbstractFactory<SdlImage> *SdlImage::factory = new AbstractFactory<SdlImage>;

SdlImage::SdlImage()
	: Image()
	, surface(NULL)
{
}

SdlImage::SdlImage(const boost::filesystem::path &uri)
	: Image()
	, surface(NULL)
{
	if (!(SDL_INIT_VIDEO & SDL_WasInit(SDL_INIT_EVERYTHING))) throw std::runtime_error(
		"SdlImage::SdlImage(uri): SDL video not initialized."
	);

	// Load the filename.
	SDL_Surface *rawImage = IMG_Load(uri.string().c_str());

	// Optimize it before returning it.
	if (rawImage) {

		surface = SDL_DisplayFormatAlpha(rawImage);

		// And kill the original.
		SDL_FreeSurface(rawImage);
	}
	else {

		throw std::runtime_error(
			"SdlImage::SdlImage(uri): IMG_Load failed. SDL says: " + std::string(SDL_GetError())
		);
	}

	if (!surface) throw std::runtime_error(
		"SdlImage::SdlImage(uri): SDL_DisplayFormatAlpha failed. SDL says: " + std::string(SDL_GetError())
	);

	setUri(uri);
}

SdlImage::~SdlImage() {
	if (surface) SDL_FreeSurface(surface);
}

int SdlImage::height() const {
	if (NULL == surface) return 0;

	return surface->h;
}

void SdlImage::render(int x, int y, Canvas *destination, int alpha, DrawMode mode, int sx, int sy, int sw, int sh) const {
	if (NULL == surface) return;

	SDL_Surface *otherSurface = Canvas::superCast<SdlCanvas>(destination)->surface;

	// If src_rect doesn't have a valid width or height, set them
	// to this Image object's dimensions.
	if (0 == sw || 0 == sh) {
		sw = width();
		sh = height();
	}

	// SDL's blitting sucks ass. I need to fucking learn OpenGL already! Damn
	// it!!!
	if (0 == alpha) {

		// Woohoo!
		return;
	}
	else {

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
		int dw = otherSurface->w;
		int dh = otherSurface->h;

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

		int dIdx = dy * otherSurface->w + dx;

		// 32-bit implied; we ain't fucking around with no bullshit!
		SDL_LockSurface(surface);
		SDL_LockSurface(otherSurface);

		// Take addresses of the first pixel of the source and destination.
		unsigned int *src = (unsigned int *)surface->pixels, *dst = (unsigned int *)otherSurface->pixels;
		unsigned char *sc;

		src += sIdx;
		dst += dIdx;

		// For each pixel from the source image, make it a
		// 2 x 2 block in the destination.
		for (int y = 0; y < sh; ++y) {
			for (int x = 0; x < sw; ++x) {

				sc = reinterpret_cast<unsigned char *>(src);

				int dstColor;
				if (DrawMode_PixelCopy == mode) {
					*dst = *src;
				}
				else if (DrawMode_Replace == mode || (255 == alpha && 255 == sc[3])) {
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
			dst += otherSurface->w;
			src -= sw;
			src += surface->w;
		}

		SDL_UnlockSurface(otherSurface);
		SDL_UnlockSurface(surface);
	}
}

int SdlImage::width() const {
	if (NULL == surface) return 0;

	return surface->w;
}

}

