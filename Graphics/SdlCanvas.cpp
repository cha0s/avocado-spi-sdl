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
	, _surface(NULL)
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

	_surface = SDL_DisplayFormatAlpha(unoptimized);
	if (NULL == _surface) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(): SDL_DisplayFormatAlpha failed. SDL says: " + std::string(SDL_GetError())
	);

	SDL_FreeSurface(unoptimized);
}

SdlCanvas::SdlCanvas(const boost::filesystem::path &uri)
	: Canvas()
	, _surface(NULL)
{
	if (!(SDL_INIT_VIDEO & SDL_WasInit(SDL_INIT_EVERYTHING))) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(uri): SDL video not initialized."
	);

	// Load the filename.
	SDL_Surface *rawImage = IMG_Load(uri.string().c_str());

	// Optimize it before returning it.
	if (rawImage) {

		_surface = SDL_DisplayFormatAlpha(rawImage);

		// And kill the original.
		SDL_FreeSurface(rawImage);
	}
	else {

		throw std::runtime_error(
			"SdlCanvas::SdlCanvas(uri): IMG_Load failed. SDL says: " + std::string(SDL_GetError())
		);
	}

	if (!_surface) throw std::runtime_error(
		"SdlCanvas::SdlCanvas(uri): SDL_DisplayFormatAlpha failed. SDL says: " + std::string(SDL_GetError())
	);

	setUri(uri);
}

SdlCanvas::~SdlCanvas() {
	if (_surface) SDL_FreeSurface(_surface);
}

unsigned int SdlCanvas::pixelAt(int x, int y) const {
	if (NULL == _surface) return 0;

	if (x < 0 || y < 0 || x >= width() || y >= height()) return 0;

	return ((unsigned int *)_surface->pixels)[y * width() + x];
}

void SdlCanvas::drawCircle(int x, int y, int radius, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _surface) return;

	filledCircleRGBA(
		_surface,
		x, y,
		radius,
		r, g, b, 255.0 * GraphicsService::BlendMode_Blend == blendMode ? a : 1.0
	);
}

void SdlCanvas::drawFilledBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _surface) return;

	boxRGBA(
		_surface,
		x, y, x + w - 1, y + h - 1,
		r, g, b, 255.0 * GraphicsService::BlendMode_Blend == blendMode ? a : 1.0
	);
}

void SdlCanvas::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _surface) return;

	lineRGBA(
		_surface,
		x1, y1, x2, y2,
		r, g, b, 255.0 * GraphicsService::BlendMode_Blend == blendMode ? a : 1.0
	);
}

void SdlCanvas::drawLineBox(int x, int y, int w, int h, int r, int g, int b, double a, GraphicsService::BlendMode blendMode) {
	if (NULL == _surface) return;

	rectangleRGBA(
		_surface,
		x, y, x + w - 1, y + h - 1,
		r, g, b, 255.0 * GraphicsService::BlendMode_Blend == blendMode ? a : 1.0
	);
}

void SdlCanvas::fill(int r, int g, int b, double a) {
	if (NULL == _surface) return;

	SDL_Rect rect = {0, 0, width(), height()};
	SDL_FillRect(_surface, &rect, SDL_MapRGBA(_surface->format, r, g, b, a * 255.0));
}

int SdlCanvas::height() const {
	if (NULL == _surface) return 0;

	return _surface->h;
}

void SdlCanvas::saveToFile(const boost::filesystem::path &filename) {
	AVOCADO_UNUSED(filename);
}

void SdlCanvas::setPixelAt(int x, int y, unsigned int pixel) {
	if (NULL == _surface) return;

	if (x < 0 || y < 0 || x >= width() || y >= height()) return;

	((unsigned int *)_surface->pixels)[y * width() + x] = pixel;
}

int SdlCanvas::width() const {
	if (NULL == _surface) return 0;

	return _surface->w;
}

SDL_Surface *SdlCanvas::surface() {
	return _surface;
}

}

