#include <application/input.hpp>

namespace application {
  namespace input {
    interaction_utils::Buttons const * buttons = nullptr;
    pic12f509::Pic12f509Interface const * pic = nullptr;
    LiquidCrystal_I2C * lcd = nullptr;
    at24c32::Interface const * eeprom = nullptr;
  }
}


