#include <application.hpp>

namespace application {

  void end() {
    delete input::pic;
    delete input::eeprom;

    input::lcd->clear();
    input::lcd->setCursor(1, 0);
    input::lcd->print("Press any key");
    input::lcd->setCursor(3, 1);
    input::lcd->print("to restart");

    input::buttons->wait_press();

    delete input::buttons;
  }

  void run() {
    input::lcd->init();
    input::lcd->backlight();
    input::lcd->noAutoscroll();
    input::lcd->setCursor(0, 0);
    delay(1000);


    String menu_options[] = {
      "Display Values",
      "Display Config",
      "Explore Content",
      "Erase Prog Memo",
      "Eeprom",
      "Exit"
    };
    interaction_utils::LcdI2CMenu * menu = new interaction_utils::LcdI2CMenu(
        input::lcd,
        input::buttons,
        menu_options,
        6
    );

    bool exit_loop = false;
    while (!exit_loop) {

      uint8_t selected_option = menu->select(0, 1, 2);

      // do action
      if (selected_option == 0) {
        screen::display_pic_values::run();
      } else if (selected_option == 1) {
        screen::display_configuration_values::run();
      } else if (selected_option == 2) {
        screen::explore_content::run();
      } else if (selected_option == 3) {
        screen::erase_programming_memory::run();
      } else if (selected_option == 4) {
        screen::eeprom::menu::run();
      } else if (selected_option == 5) {
        exit_loop = true;
      }
    }

  }
}
