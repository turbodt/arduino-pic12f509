#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_EDIT_CONTENT
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_EDIT_CONTENT

#include <Arduino.h>
#include <application/input.hpp>
#include <application/utils.hpp>
#include <application/screen/display_buffer_content.hpp>
#include <pic12f509.interface.hpp>
#include <interaction_utils.hpp>

using namespace application;

namespace screen {
  namespace edit_content {
    void run(
      pic12f509::addr_t const &,
      pic12f509::word_t * const,
      uint8_t const &
    );
  }
}

#endif
