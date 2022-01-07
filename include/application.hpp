#ifndef INCLUDE_PIC12F509_APPLICATION
#define INCLUDE_PIC12F509_APPLICATION

#include <Arduino.h>
#include <application/input.hpp>
#include <interaction_utils.hpp>
#include <at24c32.interface.hpp>
#include <application/screen/explore_content.hpp>
#include <application/screen/eeprom/menu.hpp>
#include <application/screen/display_pic_values.hpp>
#include <application/screen/display_configuration_values.hpp>
#include <application/screen/erase_programming_memory.hpp>

namespace application {

  void init();
  void run();
  void end();

}

#endif
