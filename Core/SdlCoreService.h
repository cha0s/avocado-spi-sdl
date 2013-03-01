#ifndef AVOCADO_SDLCORESERVICE_H
#define AVOCADO_SDLCORESERVICE_H

#include "main/avocado-global.h"

#include "SPI/Abstract/Core//CoreService.h"

namespace avo {

/**
 * @addtogroup Core
 * @{
 */

/**
 * @ingroup SDL
 * @{
 */

/**
 * @ingroup SPI
 * @{
 */

/**
 * The %SdlCoreService SPI implementation handles initialization and quitting
 * SDL library.
 */
class SdlCoreService : public CoreService {

public:

	/**
	 * Initialize SDL.
	 */
	SdlCoreService();

	~SdlCoreService();

	/**
	 * Quit SDL.
	 */
	void close();

	static AbstractFactory<SdlCoreService> *factory;

};

/**
 * @ingroup Manufacturing
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlCoreService> : public AbstractFactory<CoreService> {

public:

	virtual ~AbstractFactory<SdlCoreService>() {}

	/**
	 * Create a concrete CoreService.
	 */
	SdlCoreService *create() { return new SdlCoreService() ; }

};

/**
 * @}
 */

/**
 * @}
 */

}

#endif // AVOCADO_SDLCORESERVICE_H
