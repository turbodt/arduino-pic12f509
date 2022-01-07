#include <application/utils.hpp>

namespace application {

  String utils::word_hex_str = String("XXX");
  String utils::word_bin_str = String("XXXX XXXX XXXX");
  char utils::hexToChar(uint8_t const & value) {
    if (value == 0) {
      return '0';
    } else if (value == 1) {
      return '1';
    } else if (value == 2) {
      return '2';
    } else if (value == 3) {
      return '3';
    } else if (value == 4) {
      return '4';
    } else if (value == 5) {
      return '5';
    } else if (value == 6) {
      return '6';
    } else if (value == 7) {
      return '7';
    } else if (value == 8) {
      return '8';
    } else if (value == 9) {
      return '9';
    } else if (value == 10) {
      return 'A';
    } else if (value == 11) {
      return 'B';
    } else if (value == 12) {
      return 'C';
    } else if (value == 13) {
      return 'D';
    } else if (value == 14) {
      return 'E';
    } else if (value == 15) {
      return 'F';
    }
    return 'X';
  }

  String & utils::word_to_str(pic12f509::word_t word) {
    for (uint8_t i = 0; i < 3; i++) {
      uint8_t p = 1;
      uint8_t value = 0;
      for (uint8_t j = 0; j < 4; j++) {
        bool b = word % 2;
        if (b) {
          value += p;
        }
        p = p << 1;
        word = word >> 1;
      }
      word_hex_str[2-i] = hexToChar(value);
    }
    return word_hex_str;
  }

  String & utils::word_to_bin_str(pic12f509::word_t word) {
    for (uint8_t i = 0; i < 3; i++) {
      for (uint8_t j = 0; j < 4; j++) {
        bool b = word % 2;
        if (b) {
          word_bin_str[14 - (i * 5 + j) -1] = '1';
        } else {
          word_bin_str[14 - (i * 5 + j) -1] = '0';
        }
        word = word >> 1;
      }
    }
    return word_bin_str;
  }

  pic12f509::word_t utils::input_word(
    uint8_t const & col,
    uint8_t const & row,
    pic12f509::word_t value
  ) {
    uint8_t place = 3;
    while (place) {
      input::lcd->setCursor(col, row);
      input::lcd->print(utils::word_to_str(value));
      input::lcd->setCursor(col + 3 - place, row);
      input::lcd->blink_on();

      uint8_t button = input::buttons->wait_first_press();
      input::lcd->blink_off();

      if (button == 0) {
        place--;
      } else if (button == 1) {
        pic12f509::addr_t mask = 0xf << ((place - 1) * 4);
        pic12f509::addr_t umask = ~mask;
        pic12f509::addr_t digit = ((value & mask)>> ((place - 1) * 4));
        if (digit) {
          digit--;
        } else {
          digit = 0x0f;
        }
        digit = digit & 0xf;
        digit = digit << ((place -1) * 4);
        value = (value & umask) + digit;

      } else if (button == 2) {
        pic12f509::addr_t mask = 0xf << ((place - 1) * 4);
        pic12f509::addr_t umask = ~mask;
        pic12f509::addr_t digit = ((value & mask)>> ((place - 1) * 4));
        digit++;
        digit = digit & 0xf;
        digit = digit << ((place -1) * 4);
        value = (value & umask) + digit;
      }
    }
    return value;
  }

  pic12f509::addr_t utils::input_address(
    uint8_t const & col,
    uint8_t const & row,
    pic12f509::word_t value
  ) {
    return utils::input_word(col, row, value);
  }
}
