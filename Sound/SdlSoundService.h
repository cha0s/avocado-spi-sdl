#ifndef AVOCADO_SDLSOUNDSERVICE_H
#define AVOCADO_SDLSOUNDSERVICE_H

#include "core/avocado-global.h"

#include "core/Sound/SoundService.h"

namespace avo {

/**
 * @addtogroup Sound
 * @{
 */

/**
 * @ingroup SDL
 * @ingroup SPI
 */
class SdlSoundService : public SoundService {

public:

	SdlSoundService();
	~SdlSoundService();

	void close();

	static AbstractFactory<SdlSoundService> *factory;

};

/**
 * @ingroup Manufacturing
 * @ingroup SDL
 * @ingroup SPI
 */
template <>
class AbstractFactory<SdlSoundService> : public AbstractFactory<SoundService> {

public:

	virtual ~AbstractFactory<SdlSoundService>() {}

	SdlSoundService *create() { return new SdlSoundService(); }

};

/**
 * @}
 */

}

#endif // AVOCADO_SDLSOUNDSERVICE_H
