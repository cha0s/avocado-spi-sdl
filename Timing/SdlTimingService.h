#ifndef AVOCADO_SDLTIMINGSERVICE_H
#define AVOCADO_SDLTIMINGSERVICE_H

#include "main/avocado-global.h"

#include "SPI/Abstract/Timing/TimingService.h"

namespace avo {

/**
 * @addtogroup Timing
 * @{
 */

/**
 * @ingroup SDL
 * @ingroup SPI
 */
class SdlTimingService : public TimingService {

public:

	SdlTimingService();
	~SdlTimingService();

	void close();

	void sleep(int ms);

	static AbstractFactory<SdlTimingService> *factory;

};

/**
 * @ingroup SDL
 * @ingroup Manufacturing
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlTimingService> : public AbstractFactory<TimingService> {

public:

	virtual ~AbstractFactory<SdlTimingService>() {}

	SdlTimingService *create() { return new SdlTimingService(); }

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLTIMINGSERVICE_H
