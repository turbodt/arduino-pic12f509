#include <application/screen/display_pic_values.hpp>

namespace screen {

  void display_pic_values::run() {

    pic12f509::word_t osccal = 0;
    pic12f509::word_t conf_word = 0;
    pic12f509::word_t reset_vector = 0;

    input::lcd->clear();
    input::lcd->setCursor(0, 0);
    input::lcd->print("Reading...");

    input::pic->init();

    // Conf word is only readable before first CMD_INCREMENT_ADDRESS
    input::pic->send_command(pic12f509::CMD_READ_DATA);
    conf_word = input::pic->get_word();

    // PC starts at the end
    input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);

    for (pic12f509::addr_t i = 0; i < pic12f509::MEM_LEN ; i++) {
      if ( i == pic12f509::LOC_OSCCAL_VALUE ) {
        input::pic->send_command(pic12f509::CMD_READ_DATA);
        osccal = input::pic->get_word();
      } else if (i == pic12f509::LOC_RESET_VECTOR) {
        input::pic->send_command(pic12f509::CMD_READ_DATA);
        reset_vector = input::pic->get_word();
      }
      input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
    }
    input::pic->end();

    // display info
    String headers[] = {
      "Reset Vector",
      "OSCCAL Bkp",
      "Config Word"
    };
    pic12f509::word_t const values[] = {reset_vector, osccal, conf_word};
    const uint8_t num_pages = 3;

    bool exit_loop = false;
    uint8_t page_index = 0;
    uint8_t value_base = 0;
    const uint8_t num_value_base = 3;
    while (!exit_loop) {
      input::lcd->clear();
      input::lcd->setCursor(0, 0);
      input::lcd->print('<');
      input::lcd->setCursor(15, 0);
      input::lcd->print('>');

      if (page_index == num_pages) {
        input::lcd->setCursor(6, 0);
        input::lcd->print("Back");
      } else {
        input::lcd->setCursor((16 - headers[page_index].length()) / 2, 0);
        input::lcd->print(headers[page_index]);

        String value_str;
        if (value_base == 0) {
          value_str = utils::word_to_str(values[page_index]) + "h";
        } else if (value_base == 1) {
          value_str = utils::word_to_bin_str(values[page_index]) + "b";
        } else if (value_base == 2) {
          value_str = String(values[page_index]) + "d";
        }
        input::lcd->setCursor((17 - value_str.length()) / 2, 1);
        input::lcd->print(value_str);
      }

      uint8_t button = input::buttons->wait_first_press();

      if (button == 1) {
        page_index = (page_index -1 + num_pages + 1) % (num_pages + 1);
      } else if (button == 2) {
        page_index = (page_index +1) % (num_pages + 1);
      } else if (button != 0) {
        // this should never happen
      } else if (page_index == num_pages) {
        // go back
        exit_loop = true;
      } else {
        // change base
        value_base = (value_base + 1) % num_value_base;
      }
    }
  }
}
