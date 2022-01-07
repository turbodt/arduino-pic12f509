#include <application/screen/display_content.hpp>

namespace screen {

  void display_content::run(
    pic12f509::addr_t const & initial_addr
  ) {

    input::pic->init();

    pic12f509::addr_t initial_addr_trunc = initial_addr - (initial_addr % 3);

    bool exit_loop = false;
    pic12f509::addr_t content_buffer[6];
    pic12f509::addr_t curr_addr = 0;

    input::lcd->clear();
    input::lcd->setCursor(0, 0);
    input::lcd->print("Reading...");

    // PC starts at the end
    input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
    for (pic12f509::addr_t i = 0; i < initial_addr_trunc ; i++) {
      input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
      curr_addr++;
      /*
       * The following code is cool, but makes the task too slow:
       *

      String pag_str = String(i) + " of " + String(initial_addr);
      input::lcd->setCursor(8 - pag_str.length() / 2, 1);
      input::lcd->print(pag_str);
      */
    }

    pic12f509::addr_t content_buffer_addr = curr_addr;
    while(!exit_loop) {
      uint8_t len = min(6, pic12f509::MEM_LEN - content_buffer_addr);
      while ( curr_addr < content_buffer_addr + len ) {
        input::pic->send_command(pic12f509::CMD_READ_DATA);
        content_buffer[curr_addr - content_buffer_addr] = input::pic->get_word();
        input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
        curr_addr++;
      }

      display_buffer_content::run(content_buffer_addr, &content_buffer[0], len);
      uint8_t pressed_btn = input::buttons->wait_first_press();

      if (pressed_btn == 2 && curr_addr < pic12f509::MEM_LEN - 1) {
        content_buffer_addr += len;
      } else if (pressed_btn == 0) {
        input::lcd->setCursor(0, 1);
        input::lcd->print("Cancel Edit Back");
        uint8_t pressed_btn_2 = input::buttons->wait_first_press();
        switch (pressed_btn_2) {
          case 0:
            exit_loop = true;
            break;
          case 1:
            // do nothing
            break;
          case 2:
            // edit
            input::pic->end();
            edit_content::run(content_buffer_addr, &content_buffer[0], len);
            input::pic->init();
            curr_addr = 0;
            input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
            for (pic12f509::addr_t i = 0; i < content_buffer_addr ; i++) {
              input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
              curr_addr++;
            }
            content_buffer_addr = curr_addr;
            break;
        }
      } else {
        // ignore that button
      }
    }

    input::pic->end();
  }
}
