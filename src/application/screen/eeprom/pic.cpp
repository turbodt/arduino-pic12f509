#include <application/screen/eeprom/pic.hpp>


namespace screen {

  void eeprom::pic::pic_to_eeprom(uint8_t const & slot_index) {
    at24c32::addr_t slot_addr = eeprom::get_slot_address(slot_index);
    input::lcd->clear();
    input::lcd->setCursor(0,0);
    input::lcd->print("Coping from PIC");
    input::lcd->setCursor(2,1);
    input::lcd->print("to eeprom...");

    pic12f509::word_t pair_instructions[2];
    input::pic->init();
    input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
    for(uint16_t i = 0; i < pic12f509::USER_MEM_LEN; i++) {
      input::pic->send_command(pic12f509::CMD_READ_DATA);
      pair_instructions[i%2]= input::pic->get_word();
      if (i%2) {
        uint16_t j = slot_addr + 3*((i-1)/2);
        input::eeprom->send_word(j, (pair_instructions[0] >> 4) & 0x0ff);
        input::eeprom->send_word(
          j + 1,
          ((pair_instructions[0] << 4) & 0x0f0)
          | ((pair_instructions[1] >> 8) & 0x00f)
        );
        input::eeprom->send_word(j + 2, pair_instructions[1] & 0x0ff);
      }
      input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
    }
    input::pic->end();

    input::lcd->clear();
    input::lcd->setCursor(6,0);
    input::lcd->print("Done!");
    input::buttons->wait_first_press();
  }

  void eeprom::pic::eeprom_to_pic(uint8_t const & slot_index) {
    at24c32::addr_t slot_addr = eeprom::get_slot_address(slot_index);
    input::lcd->clear();
    input::lcd->setCursor(2,0);
    input::lcd->print("Coping from");
    input::lcd->setCursor(0,1);
    input::lcd->print("eeprom to pic...");

    at24c32::word_t word_buffer[3];
    input::pic->init();
    input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
    input::eeprom->init_sequential_read(slot_addr);
    for(uint16_t i = 0; i < eeprom::SLOT_MEM_LEN; i++) {
      word_buffer[i%3] = input::eeprom->get_next_word();
      if (i%3 == 2) {
         pic12f509::word_t first_word = ((((uint16_t)word_buffer[0]) << 4) & 0xff0)
           | ((((uint16_t)word_buffer[1]) >> 4) & 0x00f);
         pic12f509::word_t second_word = ((((uint16_t)word_buffer[1]) << 8) & 0xf00)
           | ((((uint16_t)word_buffer[2])) & 0x0ff);
         input::pic->send_command(pic12f509::CMD_LOAD_DATA);
         input::pic->send_word(first_word);
         input::pic->send_command(pic12f509::CMD_BEGIN_PROGRAMMING);
         input::pic->send_command(pic12f509::CMD_END_PROGRAMMING);
         input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
         input::pic->send_command(pic12f509::CMD_LOAD_DATA);
         input::pic->send_word(second_word);
         input::pic->send_command(pic12f509::CMD_BEGIN_PROGRAMMING);
         input::pic->send_command(pic12f509::CMD_END_PROGRAMMING);
         input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
      }
    }
    input::eeprom->end_sequential_read();
    input::pic->end();

    input::lcd->clear();
    input::lcd->setCursor(6,0);
    input::lcd->print("Done!");
    input::buttons->wait_first_press();
  }


  void eeprom::pic::run(uint8_t const & slot_index) {
    String menu_options[] = {
      "Copy from PIC",
      "Copy to PIC",
      "Back"
    };
    interaction_utils::LcdI2CMenu * menu = new interaction_utils::LcdI2CMenu(
        input::lcd,
        input::buttons,
        menu_options,
        3
    );

    bool exit_loop = false;
    while (!exit_loop) {

      uint8_t selected_option = menu->select(0, 1, 2);

      switch (selected_option) {
        case 0:
          pic::pic_to_eeprom(slot_index);
          break;
        case 1:
          pic::eeprom_to_pic(slot_index);
          break;
        case 2:
          exit_loop = true;
          break;
      }
    }
    delete menu;
  }
}
