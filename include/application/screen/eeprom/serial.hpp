#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_SERIAL
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_SERIAL

#include <Arduino.h>
#include <application/input.hpp>
#include <application/screen/eeprom/shared.hpp>
#include <interaction_utils.hpp>
#include <at24c32.interface.hpp>
#include <at24c32.operations.hpp>
#include <pic12f509.interface.hpp>
#include <serial-comm.hpp>

using namespace application;

namespace screen {
  namespace eeprom {
    namespace serial {
      void eeprom_to_serial(uint8_t const &);
      void serial_to_eeprom(uint8_t const &);
      void run(uint8_t const &);
    }
  }
}

#endif
