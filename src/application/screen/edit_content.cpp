#include <application/screen/edit_content.hpp>

namespace screen {

  void edit_content::run(
    pic12f509::addr_t const & initial_addr,
    pic12f509::word_t * const content_buffer,
    uint8_t const & len
  ) {

    input::pic->init();

    bool exit_loop = false;
    pic12f509::addr_t curr_addr = 0;

    input::lcd->clear();
    input::lcd->setCursor(0, 0);
    input::lcd->print("Reading...");

    // PC starts at the end
    input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);

    for (pic12f509::addr_t i = 0; i < initial_addr ; i++) {
      input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
      curr_addr++;
    }

    // copy buffer
    pic12f509::word_t new_content_buffer[len];
    for (uint8_t i = 0; i < len ; i++) {
      new_content_buffer[i] = content_buffer[i];
    }

    while(!exit_loop) {

      display_buffer_content::run(curr_addr, &new_content_buffer[0], len);
      for (uint8_t i = 0; i < len; ) {
        for (uint8_t j = 0; j < 3 && i < len; j++) {
          new_content_buffer[i] = utils::input_word(5 + j * 4, i / 3, new_content_buffer[i]);
          i++;
        }
      }
      uint8_t pressed_btn = input::buttons->wait_first_press();

      if (pressed_btn == 1) {
        // Cancel
        exit_loop = true;
        input::lcd->clear();
        input::lcd->setCursor(4, 0);
        input::lcd->print("Writting");
        input::lcd->setCursor(4, 1);
        input::lcd->print("canceled");
        delay(2000);
      } else if (pressed_btn == 0) {
        // write values
        exit_loop = true;
        input::lcd->clear();
        input::lcd->setCursor(0, 0);
        input::lcd->print("Writting...");

        bool writting_error = false;
        for (uint8_t i = 0; i < len && !writting_error ; i++) {
          // load and write word
          input::pic->send_command(pic12f509::CMD_LOAD_DATA);
          input::pic->send_word(new_content_buffer[i]);
          input::pic->send_command(pic12f509::CMD_BEGIN_PROGRAMMING);
          input::pic->send_command(pic12f509::CMD_END_PROGRAMMING);
          // read word from memory
          input::pic->send_command(pic12f509::CMD_READ_DATA);
          pic12f509::word_t word = input::pic->get_word();
          // update buffer
          content_buffer[i] = word;
          // increment address
          input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
          // raise error if any
          writting_error = word != new_content_buffer[i];
        }

        if (writting_error) {
          input::lcd->clear();
          input::lcd->setCursor(1, 0);
          input::lcd->print("Error Writting");
          delay(2000);
        }

      } else {
        // ignore that button
      }
    }

    input::pic->end();
  }
}
