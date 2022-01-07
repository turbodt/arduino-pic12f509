#include <application/screen/display_buffer_content.hpp>

namespace screen {

  void display_buffer_content::run(
    pic12f509::addr_t const & curr_addr,
    pic12f509::word_t const * const p_word,
    uint8_t const & len
  ) {
    pic12f509::word_t const * p_value = p_word;

    input::lcd->clear();
    input::lcd->setCursor(0, 0);
    input::lcd->print(utils::word_to_str(curr_addr));
    input::lcd->print(':');

    if (len >= 1) {
      input::lcd->print(' ');
      input::lcd->print(utils::word_to_str(*p_value));
      p_value++;
    }

    if (len >= 2) {
      input::lcd->print(' ');
      input::lcd->print(utils::word_to_str(*p_value));
      p_value++;
    }

    if (len >= 3) {
      input::lcd->print(' ');
      input::lcd->print(utils::word_to_str(*p_value));
      p_value++;
    }

    if (len >= 4) {
      input::lcd->setCursor(0, 1);
      input::lcd->print(utils::word_to_str(curr_addr + 3));
      input::lcd->print(':');

      input::lcd->print(' ');
      input::lcd->print(utils::word_to_str(*p_value));
      p_value++;
    }

    if (len >= 5) {
      input::lcd->print(' ');
      input::lcd->print(utils::word_to_str(*p_value));
      p_value++;
    }

    if (len >= 6) {
      input::lcd->print(' ');
      input::lcd->print(utils::word_to_str(*p_value));
      p_value++;
    }
  }
}
