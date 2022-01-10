#include "serial-comm.hpp"

namespace serial_comm {

  SerialPort::SerialPort() {}

  SerialPort::~SerialPort() {
    this->end();
  }

  SerialPort * SerialPort::start() {
    this->received_bytes_cnt = 0;
    this->reciving_content_size = 0;

    Serial.begin(9600);
    while(!Serial) {}
    while (Serial.available()) {
      Serial.read();
    }
    return this;
  }

  SerialPort * SerialPort::end() {
    Serial.flush();
    Serial.end();
    return this;
  }

  SerialPort const * SerialPort::send_ack() const {
    Serial.write((uint8_t)0);
    return this;
  }

  SerialPort * SerialPort::init_reception() {
    this->start();
    while ((unsigned int) Serial.available() < sizeof(unsigned long)) {}
    Serial.readBytes((uint8_t *)&this->reciving_content_size, sizeof(unsigned long));
    return this;
  };

  SerialPort * SerialPort::end_reception() {
    this->end();
    return this;
  }

  uint8_t SerialPort::get_next_word() {
    uint8_t word;
    while ((unsigned int) Serial.available() < sizeof(uint8_t)) {}
    Serial.readBytes(&word, sizeof(uint8_t));
    this->received_bytes_cnt++;
    if (
      !(this->received_bytes_cnt % BUFFER_SIZE)
      || this->is_content_finished()
    ) {
      this->send_ack();
    }
    return word;
  }

  bool SerialPort::is_content_finished() const {
    return this->received_bytes_cnt >= this->reciving_content_size;
  }

  unsigned long SerialPort::get_reciving_content_size() const {
    return this->reciving_content_size;
  }

  unsigned long SerialPort::get_received_size() const {
    return this->received_bytes_cnt;
  }
}
