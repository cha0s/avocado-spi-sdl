#include "main/avocado-global.h"

#include <boost/extension/extension.hpp>

#include "SdlSoundService.h"

/**
 * @addtogroup SPI
 * @{
 */

extern "C"
void BOOST_EXTENSION_EXPORT_DECL
implementSpi(avo::FactoryManager<AVOCADO_SPI(Sound, Sdl)> &manager) {

	manager.setInstance(avo::SdlSoundService::factory);
}

/**
 * @}
 */
