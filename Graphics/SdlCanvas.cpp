#include "core/avocado-global.h"

#include "SdlCanvas.h"

#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"

enum SDL_ColorMask {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	SDL_ColorMaskRed = 0xff000000,
	SDL_ColorMaskGreen = 0x00ff0000,
	SDL_ColorMaskBlue = 0x0000ff00,
	SDL_ColorMaskAlpha = 0x000000ff
#else
	SDL_ColorMaskRed = 0x000000ff,
	SDL_ColorMaskGreen = 0x0000ff00,
	SDL_ColorMaskBlue = 0x00ff0000,
	SDL_ColorMaskAlpha = 0xff000000
#endif
};

namespace avo {

AbstractFactory<SdlCanvas> *SdlCanvas::factory = new AbstractFactory<SdlCanvas>;

SdlCanvas::SdlCanvas()
	: Canvas()
	, surface(NULL)
{
}

SdlCanvas::SdlCanvas(int width, int height)
	: Canvas()
{
	if (!(SDL_INIT_VIDEO & SDL_WasInit(SDL_INIT_EVERYTHING))) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(): SDL video not initialized."
	);

	SDL_Surface *unoptimized = SDL_CreateRGBSurface(
		SDL_SRCALPHA,
		width,
		height,
		32,
		SDL_ColorMaskRed,
		SDL_ColorMaskGreen,
		SDL_ColorMaskBlue,
		SDL_ColorMaskAlpha
	);
	if (NULL == unoptimized) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(): SDL_CreateRGBSurface failed. SDL says: " + std::string(SDL_GetError())
	);

	surface = SDL_DisplayFormatAlpha(unoptimized);
	if (NULL == surface) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(): SDL_DisplayFormatAlpha failed. SDL says: " + std::string(SDL_GetError())
	);

	SDL_FreeSurface(unoptimized);
}

SdlCanvas::SdlCanvas(const boost::filesystem::path &uri)
	: Canvas()
	, surface(NULL)
{
	if (!(SDL_INIT_VIDEO & SDL_WasInit(SDL_INIT_EVERYTHING))) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(uri): SDL video not initialized."
	);

	// Load the filename.
	SDL_Surface *rawImage = IMG_Load(uri.c_str());

	// Optimize it before returning it.
	if (rawImage) {

		surface = SDL_DisplayFormatAlpha(rawImage);

		// And kill the original.
		SDL_FreeSurface(rawImage);
	}
	else {

		throw std::runtime_error(
			"SdlCanvas::SdlCanvas(uri): IMG_Load failed. SDL says: " + std::string(SDL_GetError())
		);
	}

	if (!surface) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(uri): SDL_DisplayFormatAlpha failed. SDL says: " + std::string(SDL_GetError())
	);

	setUri(uri);
}

SdlCanvas::~SdlCanvas() {
	if (surface) SDL_FreeSurface(surface);
}

unsigned int SdlCanvas::pixelAt(int x, int y) const {
	if (NULL == surface) return 0;

	if (x < 0 || y < 0 || x >= width() || y >= height()) return 0;

	return ((unsigned int *)surface->pixels)[y * width() + x];
}

void SdlCanvas::drawCircle(int x, int y, int radius, int r, int g, int b, int a, DrawMode drawMode) {
	AVOCADO_UNUSED(drawMode);
	if (NULL == surface) return;

	filledCircleRGBA(
		surface,
		x, y,
		radius,
		r, g, b, a
	);
}

void SdlCanvas::drawFilledBox(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {
	AVOCADO_UNUSED(drawMode);
	if (NULL == surface) return;

	boxRGBA(
		surface,
		x, y, x + w - 1, y + h - 1,
		r, g, b, a
	);
}

void SdlCanvas::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a, DrawMode drawMode) {
	AVOCADO_UNUSED(drawMode);
	if (NULL == surface) return;

	lineRGBA(
		surface,
		x1, y1, x2, y2,
		r, g, b, a
	);
}

void SdlCanvas::drawLineBox(int x, int y, int w, int h, int r, int g, int b, int a, DrawMode drawMode) {
	AVOCADO_UNUSED(drawMode);
	if (NULL == surface) return;

	rectangleRGBA(
		surface,
		x, y, x + w - 1, y + h - 1,
		r, g, b, a
	);
}

void SdlCanvas::fill(int r, int g, int b, int a) {
	if (NULL == surface) return;

	SDL_Rect rect = {0, 0, width(), height()};
	SDL_FillRect(surface, &rect, SDL_MapRGBA(surface->format, r, g, b, a));
}

int SdlCanvas::height() const {
	if (NULL == surface) return 0;

	return surface->h;
}

void SdlCanvas::render(int x, int y, Canvas *destination, int alpha, DrawMode mode, int sx, int sy, int sw, int sh) const {
	if (NULL == surface) return;

	SDL_Surface *otherSurface = superCast<SdlCanvas>(destination)->surface;

	// If src_rect doesn't have a valid width or height, set them
	// to this Canvas object's dimensions.
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

void SdlCanvas::saveToFile(const boost::filesystem::path &filename) {
	AVOCADO_UNUSED(filename);
}

void SdlCanvas::setPixelAt(int x, int y, unsigned int pixel) {
	if (NULL == surface) return;

	if (x < 0 || y < 0 || x >= width() || y >= height()) return;

	((unsigned int *)surface->pixels)[y * width() + x] = pixel;
}

int SdlCanvas::width() const {
	if (NULL == surface) return 0;

	return surface->w;
}

}

