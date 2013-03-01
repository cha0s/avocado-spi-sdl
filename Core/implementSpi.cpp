#include "main/avocado-global.h"

#include <boost/extension/extension.hpp>

#include "SdlCoreService.h"

/**
 * @addtogroup SPI
 * @{
 */

extern "C"
void BOOST_EXTENSION_EXPORT_DECL
implementSpi(avo::FactoryManager<AVOCADO_SPI(Core, Sdl)> &manager) {

	manager.setInstance(avo::SdlCoreService::factory);
}

/**
 * @}
 */
