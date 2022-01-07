#include <application/screen/eeprom/display_content.hpp>
namespace screen {

  void eeprom::display_content::run(
    uint8_t const & slot_index,
    pic12f509::addr_t const & initial_addr
  ) {
    at24c32::addr_t slot_addr = eeprom::get_slot_address(slot_index);
    pic12f509::addr_t curr_addr = initial_addr - (initial_addr % 3);

    bool exit_loop = false;
    pic12f509::addr_t content_buffer[6];

    input::lcd->clear();
    input::lcd->setCursor(0, 0);
    input::lcd->print("Reading...");

    while(!exit_loop) {
      uint8_t len = min(6, pic12f509::USER_MEM_LEN - curr_addr);
      at24c32::addr_t eeprom_curr_addr = pic_to_eeprom_addr(curr_addr);

      at24c32::word_t buff[2];
      input::eeprom->init_sequential_read(slot_addr + eeprom_curr_addr);
      if (curr_addr%2 == 1) {
        buff[1] = input::eeprom->get_next_word();
      }
      for (uint8_t i = 0; i < len ; i++) {
        if ((curr_addr + i)%2 == 0) {
          buff[0] = input::eeprom->get_next_word();
          buff[1] = input::eeprom->get_next_word();
          content_buffer[i] = ((((uint16_t)buff[0]) << 4) & 0xff0)
           | ((((uint16_t)buff[1]) >> 4) & 0x00f);
        } else {
          buff[0] = buff[1];
          buff[1] = input::eeprom->get_next_word();
          content_buffer[i] = ((((uint16_t)buff[0]) << 8) & 0xf00)
           | ((((uint16_t)buff[1])) & 0x0ff);
        }
      }
      input::eeprom->end_sequential_read();

      display_buffer_content::run(curr_addr, &content_buffer[0], len);
      uint8_t pressed_btn = input::buttons->wait_first_press();

      if (pressed_btn == 2 && curr_addr + len < pic12f509::USER_MEM_LEN - 1) {
        curr_addr += len;
      } else if (pressed_btn == 2) {
        curr_addr = 0;
      } else if (pressed_btn == 1 && curr_addr < 6) {
        curr_addr = pic12f509::USER_MEM_LEN - 6;
      } else if (pressed_btn == 1) {
        curr_addr -= 6;
      } else if (pressed_btn == 0) {
        exit_loop = true;
      } else {
        // do nothing
      }
    }

    input::pic->end();
  }
}
