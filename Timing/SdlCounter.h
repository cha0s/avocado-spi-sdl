#ifndef AVOCADO_SDLCOUNTER_H
#define AVOCADO_SDLCOUNTER_H

#include "main/avocado-global.h"

#include <SDL/SDL.h>

#include "SPI/Abstract/Timing/Counter.h"

namespace avo {

/**
 * @addtogroup Timing
 * @{
 */

/**
 * Counter class to count time passing between invocations.
 *
 * @ingroup SDL
 * @ingroup SPI
 */
class SdlCounter : public Counter {

public:

	/**
	 * Counter constructor. Initialize the current ticks.
	 */
	SdlCounter();

	~SdlCounter();

	static AbstractFactory<SdlCounter> *factory;

	double current();

};

/**
 * @ingroup Manufacturing
 * @ingroup SDL
 * @ingroup SPI
 */
template<>
class AbstractFactory<SdlCounter> : public AbstractFactory<Counter> {

public:

	virtual ~AbstractFactory<SdlCounter>() {}

	SdlCounter *create() { return new SdlCounter(); };

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLCOUNTER_H
