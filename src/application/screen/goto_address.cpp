#include <application/screen/goto_address.hpp>

namespace screen {
  void goto_address::run() {
    bool exit_loop = false;
    pic12f509::addr_t value = 0;
    while (!exit_loop) {
      input::lcd->clear();
      input::lcd->setCursor(0, 0);
      input::lcd->print("Go to addr:");
      value = utils::input_address(12, 0, value);

      input::lcd->setCursor(0, 1);
      input::lcd->print("Edit");
      input::lcd->setCursor(13, 1);
      input::lcd->print("Ok");
      uint8_t button = input::buttons->wait_first_press();

      if (button == 0) {
        exit_loop = true;
      } else {
        // do nothing
      }
    }
    display_content::run(value);
  }
}
