#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_SHARED
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_EEPROM_SHARED

#include <Arduino.h>
#include <application/input.hpp>
#include <at24c32.interface.hpp>
#include <pic12f509.interface.hpp>

using namespace application;

namespace screen {
  namespace eeprom {
    extern const uint16_t SLOT_MEM_LEN;
    extern const uint8_t NUM_SLOTS;
    at24c32::addr_t get_slot_address(uint8_t const &);
    at24c32::addr_t pic_to_eeprom_addr(pic12f509::addr_t const &);
  }
}

#endif
