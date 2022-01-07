#include <application/screen/eeprom/shared.hpp>

namespace screen {
  namespace eeprom {
    const uint16_t SLOT_MEM_LEN = 3*(pic12f509::USER_MEM_LEN/2);
    const uint8_t NUM_SLOTS = at24c32::MEM_LEN / SLOT_MEM_LEN;
    at24c32::addr_t get_slot_address(uint8_t const & slot_index) {
      return slot_index*SLOT_MEM_LEN;
    }
    at24c32::addr_t pic_to_eeprom_addr(pic12f509::addr_t const & addr) {
      return 3*(addr/2) + addr % 2;
    }
  }
}
