#ifndef INCLUDE_SERIAL_COMM
#define INCLUDE_SERIAL_COMM

#include <Arduino.h>

namespace serial_comm {

  const uint16_t BUFFER_SIZE = 64;

  class SerialPort {
    protected:
      unsigned long reciving_content_size;
      unsigned long received_bytes_cnt;

      SerialPort const * send_ack() const;
      SerialPort * start();
      SerialPort * end();
    public:
      SerialPort();
      ~SerialPort();
      SerialPort * init_reception();
      uint8_t get_next_word();
      SerialPort * end_reception();

      bool is_content_finished() const;
      unsigned long get_received_size() const;
      unsigned long get_reciving_content_size() const;
  };
}

#endif
