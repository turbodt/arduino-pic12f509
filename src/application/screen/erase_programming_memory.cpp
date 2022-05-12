#include <application/screen/erase_programming_memory.hpp>

namespace screen {

  void erase_programming_memory::run() {

    input::lcd->clear();
    input::lcd->setCursor(0, 0);
    input::lcd->print("Erase Prog Memo?");
    input::lcd->setCursor(0, 1);
    input::lcd->print("Yes");
    input::lcd->setCursor(14, 1);
    input::lcd->print("No");

    uint8_t selected_button = input::buttons->wait_first_press();

    if (selected_button == 1) {
      input::lcd->clear();
      input::lcd->setCursor(0, 0);
      input::lcd->print("Erasing...");

      // get CONF WORD and OSCCAL value from BKP
      input::pic->init();
      input::pic->send_command(pic12f509::CMD_READ_DATA);
      pic12f509::word_t conf_word = input::pic->get_word();
      input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
      for (pic12f509::addr_t i = 0; i < pic12f509::LOC_OSCCAL_VALUE ; i++) {
        input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
      }
      input::pic->send_command(pic12f509::CMD_READ_DATA);
      pic12f509::word_t osccal = input::pic->get_word();
      input::pic->end();

      // perform bulk erase
      input::pic->init();
      input::pic->send_command(pic12f509::CMD_BULK_ERASE);
      input::pic->end();

      // set CONF_WORD and OSCCAL value
      input::pic->init();
      input::pic->send_command(pic12f509::CMD_LOAD_DATA);
      input::pic->send_word(conf_word);
      input::pic->send_command(pic12f509::CMD_BEGIN_PROGRAMMING);
      input::pic->send_command(pic12f509::CMD_END_PROGRAMMING);
      input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
      for (pic12f509::addr_t i = 0; i < pic12f509::LOC_RESET_VECTOR ; i++) {
        input::pic->send_command(pic12f509::CMD_INCREMENT_ADDRESS);
      }
      input::pic->send_command(pic12f509::CMD_LOAD_DATA);
      input::pic->send_word(osccal);
      input::pic->send_command(pic12f509::CMD_BEGIN_PROGRAMMING);
      input::pic->send_command(pic12f509::CMD_END_PROGRAMMING);
      input::pic->end();

      // inform and return
      input::lcd->clear();
      input::lcd->setCursor(1, 0);
      input::lcd->print("Program memory");
      input::lcd->setCursor(1, 1);
      input::lcd->print("erased!");

      input::buttons->wait_first_press();
    }
  }
}
