#include "interaction_utils.hpp"
#include "pic12f509.interface.hpp"
#include <application/screen/eeprom/menu.hpp>

namespace screen {

  void eeprom::erase(uint8_t const & slot_index) {
    at24c32::addr_t slot_addr = eeprom::get_slot_address(slot_index);

    input::lcd->clear();
    input::lcd->setCursor(4,0);
    input::lcd->print("Deleting");
    input::lcd->setCursor(3,1);
    input::lcd->print("content...");
    for(uint16_t i = 0; i < eeprom::SLOT_MEM_LEN; i++) {
      input::eeprom->send_word(i + slot_addr, 0xff);
    }
    input::lcd->clear();
    input::lcd->setCursor(6,0);
    input::lcd->print("Done!");
    input::buttons->wait_first_press();

  }

  void eeprom::menu::run() {
    String slot_menu_options[eeprom::NUM_SLOTS];
    for (uint8_t i = 0 ; i < eeprom::NUM_SLOTS ; i++) {
      slot_menu_options[i] = "Slot " + String(i+1);
    }
    interaction_utils::LcdI2CMenu * slot_menu = new interaction_utils::LcdI2CMenu(
      input::lcd,
      input::buttons,
      slot_menu_options,
      eeprom::NUM_SLOTS
    );
    uint8_t slot_index = slot_menu->select(0,1,2);
    delete slot_menu;

    String menu_options[] = {
      "Comm with Serial",
      "Comm with PIC",
      "Display Content",
      "Erase",
      "Back"
    };
    interaction_utils::LcdI2CMenu * menu = new interaction_utils::LcdI2CMenu(
        input::lcd,
        input::buttons,
        menu_options,
        5
    );

    bool exit_loop = false;
    while (!exit_loop) {

      uint8_t selected_option = menu->select(0, 1, 2);

      switch (selected_option) {
        case 0:
          eeprom::serial::run(slot_index);
          break;
        case 1:
          eeprom::pic::run(slot_index);
          break;
        case 2:
          eeprom::display_content::run(slot_index);
          break;
        case 3:
          erase(slot_index);
          break;
        case 4:
          exit_loop = true;
          break;
      }
    }
    delete menu;
  }
}
