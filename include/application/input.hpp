#ifndef INCLUDE_PIC12F509_APPLICATION_INPUT
#define INCLUDE_PIC12F509_APPLICATION_INPUT

#include <LiquidCrystal_I2C.h>
#include <pic12f509.interface.hpp>
#include <at24c32.interface.hpp>
#include <interaction_utils.hpp>

namespace application {

  namespace input {
    extern interaction_utils::Buttons const * buttons;
    extern pic12f509::Pic12f509Interface const * pic;
    extern at24c32::Interface const * eeprom;
    extern LiquidCrystal_I2C * lcd;
  }

}

#endif
