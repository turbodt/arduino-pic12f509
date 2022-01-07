#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_DISPLAY_CONTENT
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_DISPLAY_CONTENT

#include <Arduino.h>
#include <application/input.hpp>
#include <application/screen/eeprom/shared.hpp>
#include <application/screen/display_buffer_content.hpp>
#include <interaction_utils.hpp>
#include <at24c32.interface.hpp>
#include <pic12f509.interface.hpp>

using namespace application;

namespace screen {
  namespace eeprom {
    namespace display_content {
      void run(uint8_t const &, pic12f509::addr_t const & = 0);
    }
  }
}

#endif
