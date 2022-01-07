#include <Arduino.h>
#include <application/input.hpp>
#include <pic12f509.interface.hpp>

namespace application {
  namespace utils {
    extern String word_hex_str;
    extern String word_bin_str;
    char hexToChar(uint8_t const &);
    String & word_to_str(pic12f509::word_t);
    String & word_to_bin_str(pic12f509::word_t);
    pic12f509::addr_t input_address(uint8_t const &, uint8_t const &, pic12f509::addr_t);
    pic12f509::word_t input_word(uint8_t const &, uint8_t const &, pic12f509::word_t);
  }
}
