#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_CONFIGURATION_PIC_VALUES
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_CONFIGURATION_PIC_VALUES

#include <Arduino.h>
#include <application/input.hpp>
#include <application/utils.hpp>
#include <pic12f509.interface.hpp>

using namespace application;

namespace screen {
  namespace display_configuration_values {
    void run();
    void set_conf_word(pic12f509::word_t const &);
    void edit_mclr(pic12f509::word_t &);
    void edit_cp(pic12f509::word_t &);
    void edit_wdt(pic12f509::word_t &);
    void edit_osc(pic12f509::word_t &);
  }
}

#endif
