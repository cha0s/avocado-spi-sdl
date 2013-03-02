#ifndef AVOCADO_SDLGRAPHICSSERVICE_H
#define AVOCADO_SDLGRAPHICSSERVICE_H

#include "core/avocado-global.h"

#include <SDL/SDL.h>

#include "core/Graphics/GraphicsService.h"

namespace avo {

/**
 * @addtogroup Graphics
 * @{
 */

/**
 * @ingroup SDL
 */
class SdlGraphicsService : public GraphicsService {

public:

	SdlGraphicsService();
	~SdlGraphicsService();

	void close();

	static AbstractFactory<SdlGraphicsService> *factory;

private:

	int numJoysticks;
	SDL_Joystick **joystick;

};

/**
 * @ingroup Manufacturing
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlGraphicsService> : public AbstractFactory<GraphicsService> {

public:

	virtual ~AbstractFactory<SdlGraphicsService>() {}

	/**
	 * Create a concrete GraphicsService.
	 */
	SdlGraphicsService *create() { return new SdlGraphicsService(); }

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLGRAPHICSSERVICE_H
