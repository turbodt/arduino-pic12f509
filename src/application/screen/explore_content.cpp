#include <application/screen/explore_content.hpp>

namespace screen {
  void explore_content::run() {
    String menu_options[] = {
      "Go To 0x000h",
      "Go To RESET VECT",
      "Go To OSCCAL BKP",
      "Go To CONF WORD",
      "Go To Addr",
      "Back"
    };
    interaction_utils::LcdI2CMenu * menu = new interaction_utils::LcdI2CMenu(
      input::lcd,
      input::buttons,
      menu_options,
      6
    );

    bool exit_loop = false;
    while (!exit_loop) {
      uint8_t option = menu->select(0, 1, 2);
      if (option == 0) {
        display_content::run();
      } else if (option == 1) {
        display_content::run(pic12f509::LOC_RESET_VECTOR);
      } else if (option == 2) {
        display_content::run(pic12f509::LOC_OSCCAL_VALUE);
      } else if (option == 3) {
        display_content::run(pic12f509::LOC_CONF_WORD);
      } else if (option == 4) {
        goto_address::run();
      } else if (option == 5) {
        exit_loop = true;
      }
    }

  }
}
