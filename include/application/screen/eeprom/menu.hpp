#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_MENU
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_MENU

#include <Arduino.h>
#include <application/input.hpp>
#include <application/screen/eeprom/shared.hpp>
#include <application/screen/eeprom/serial.hpp>
#include <application/screen/eeprom/pic.hpp>
#include <application/screen/eeprom/display_content.hpp>
#include <interaction_utils.hpp>
#include <at24c32.interface.hpp>
#include <pic12f509.interface.hpp>

using namespace application;

namespace screen {
  namespace eeprom {

    void erase(uint8_t const &);

    namespace menu {
      void run();
    }
  }
}

#endif
