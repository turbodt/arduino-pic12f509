#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_PIC
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_PIC

#include <Arduino.h>
#include <application/input.hpp>
#include <application/screen/eeprom/shared.hpp>
#include <interaction_utils.hpp>
#include <at24c32.interface.hpp>
#include <pic12f509.interface.hpp>

using namespace application;

namespace screen {
  namespace eeprom {
    namespace pic {
      void pic_to_eeprom(uint8_t const &);
      void eeprom_to_pic(uint8_t const &);
      void run(uint8_t const &);
    }
  }
}

#endif
