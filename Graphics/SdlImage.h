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

	/**
	 * Build a NULL SDL_Surface.
	 */
	SdlImage();

	/**
	 * Load an SDL_Surface from a filename.
	 */
	SdlImage(const boost::filesystem::path &uri);

	/**
	 * Destroy SDL_Surface.
	 */
	~SdlImage();

	int height() const;

	int width() const;

	SDL_Surface *surface();

	static AbstractFactory<SdlImage> *factory;

private:

	SDL_Surface *_surface;

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

	SdlImage *create() {
		return new SdlImage();
	}

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLIMAGE_H
