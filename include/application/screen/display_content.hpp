#ifndef INCLUDE_PIC12F509_APPLICATION_SCREEN_DISPLAY_CONTENT
#define INCLUDE_PIC12F509_APPLICATION_SCREEN_DISPLAY_CONTENT

#include <Arduino.h>
#include <application/input.hpp>
#include <application/screen/display_buffer_content.hpp>
#include <application/screen/edit_content.hpp>
#include <pic12f509.interface.hpp>
#include <interaction_utils.hpp>

using namespace application;

namespace screen {
  namespace display_content {
    void run(
      pic12f509::addr_t const & = 0
    );
  }
}

#endif
