#include "core/avocado-global.h"

#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"

#include "SdlCanvas.h"
#include "SdlImage.h"

namespace avo {

AbstractFactory<SdlImage> *SdlImage::factory = new AbstractFactory<SdlImage>;

SdlImage::SdlImage()
	: Image()
	, _surface(NULL)
{
}

SdlImage::SdlImage(const boost::filesystem::path &uri)
	: Image()
	, _surface(NULL)
{
	if (!(SDL_INIT_VIDEO & SDL_WasInit(SDL_INIT_EVERYTHING))) throw std::runtime_error(
		"SdlImage::SdlImage(uri): SDL video not initialized."
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
			"SdlImage::SdlImage(uri): IMG_Load failed. SDL says: " + std::string(SDL_GetError())
		);
	}

	if (!_surface) throw std::runtime_error(
		"SdlImage::SdlImage(uri): SDL_DisplayFormatAlpha failed. SDL says: " + std::string(SDL_GetError())
	);

	setUri(uri);
}

SdlImage::~SdlImage() {
	if (_surface) SDL_FreeSurface(_surface);
}

int SdlImage::height() const {
	if (NULL == _surface) return 0;

	return _surface->h;
}

int SdlImage::width() const {
	if (NULL == _surface) return 0;

	return _surface->w;
}

SDL_Surface *SdlImage::surface() {
	return _surface;
}

}

