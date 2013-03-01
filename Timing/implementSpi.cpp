#include "main/avocado-global.h"

#include <boost/extension/extension.hpp>

#include "SdlTimingService.h"

/**
 * @addtogroup SPI
 * @{
 */

extern "C"
void BOOST_EXTENSION_EXPORT_DECL
implementSpi(avo::FactoryManager<AVOCADO_SPI(Timing, Sdl)> &manager) {

	manager.setInstance(avo::SdlTimingService::factory);
}

/**
 * @}
 */
