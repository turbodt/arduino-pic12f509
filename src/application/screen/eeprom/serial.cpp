#include "application/screen/eeprom/shared.hpp"
#include <application/screen/eeprom/serial.hpp>

namespace screen {

  void eeprom::serial::eeprom_to_serial(uint8_t const & slot_index) {
    at24c32::addr_t slot_addr = eeprom::get_slot_address(slot_index);
    input::lcd->clear();
    input::lcd->setCursor(2,0);
    input::lcd->print("Sending");
    input::lcd->setCursor(3,1);
    input::lcd->print("content...");
    Serial.begin(9600);
    while(!Serial) {}
    input::eeprom->init_sequential_read(slot_addr);
    for (uint16_t i = 0; i < eeprom::SLOT_MEM_LEN; i++) {
      Serial.write(input::eeprom->get_next_word());
    }
    Serial.end();
    input::eeprom->end_sequential_read();
    input::lcd->clear();
    input::lcd->setCursor(6,0);
    input::lcd->print("Done!");
    input::buttons->wait_first_press();
  }

  /*
  void eeprom::serial::serial_to_eeprom(uint8_t const & slot_index) {
    at24c32::addr_t slot_addr = eeprom::get_slot_address(slot_index);
    Serial.begin(9600);
    while(!Serial) {}
    input::lcd->clear();
    input::lcd->setCursor(0,0);
    input::lcd->print("Ready to receive");
    input::lcd->setCursor(3,1);
    input::lcd->print("content...");
    while (Serial.available() == 0) {}
    input::lcd->clear();
    input::lcd->setCursor(4,0);
    input::lcd->print("Received");

    at24c32::SequentialWrite * writter = new at24c32::SequentialWrite(input::eeprom);
    writter->init(slot_addr);
    uint8_t buffer[1];
    for(uint16_t i = 0;i < eeprom::SLOT_MEM_LEN && Serial; i++) {
      buffer[0] = Serial.read();
      writter->send_next_word(buffer[0]);
      if (i%0xf == 0) {
        input::lcd->setCursor(2,1);
        input::lcd->print(String(i+1)+ " of " + String(eeprom::SLOT_MEM_LEN));
      }
    }
    writter->end();
    delete writter;
    Serial.end();
    input::lcd->clear();
    input::lcd->setCursor(6,0);
    input::lcd->print("Done!");
    input::buttons->wait_first_press();
  }
  */

  void eeprom::serial::serial_to_eeprom(uint8_t const & slot_index) {
    at24c32::addr_t slot_addr = eeprom::get_slot_address(slot_index);

    serial_comm::SerialPort * serial = new serial_comm::SerialPort();

    input::lcd->clear();
    input::lcd->setCursor(0,0);
    input::lcd->print("Ready to receive");
    input::lcd->setCursor(3,1);
    input::lcd->print("content...");

    serial->init_reception();

    input::lcd->clear();
    input::lcd->setCursor(0,0);
    input::lcd->print("Size "+String(serial->get_reciving_content_size()) + " Bytes");

    at24c32::SequentialWrite * writter = new at24c32::SequentialWrite(input::eeprom);
    writter->init(slot_addr);
    while (!serial->is_content_finished()) {
      if (!(serial->get_received_size() % 0xff)) {
        input::lcd->setCursor(0,1);
        input::lcd->print("Received "+String(serial->get_received_size())+" Bytes");
      }
      uint8_t word = serial->get_next_word();
      writter->send_next_word(word);
    }
    writter->end();
    delete writter;

    serial->end_reception();
    delete serial;

    input::lcd->clear();
    input::lcd->setCursor(6,0);
    input::lcd->print("Done!");
    input::buttons->wait_first_press();
  }

  void eeprom::serial::run(uint8_t const & slot_index) {
    String menu_options[] = {
      "Send",
      "Receive",
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
          serial::eeprom_to_serial(slot_index);
          exit_loop = true;
          break;
        case 1:
          serial::serial_to_eeprom(slot_index);
          exit_loop = true;
          break;
        case 2:
          exit_loop = true;
          break;
      }
    }
    delete menu;
  }
}
