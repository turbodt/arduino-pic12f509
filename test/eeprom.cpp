#include <Arduino.h>
#include <interaction_utils.hpp>
#include <at24c32.interface.hpp>
#include <LiquidCrystal_I2C.h>


#define PIN_BTN_1 A1
#define PIN_BTN_2 A3
#define PIN_BTN_3 A2

#define PIN_DATA 13
#define PIN_CLOCK 12
#define PIN_VDD 11
#define PIN_VPP 10

void setup() {
}

void loop() {
  uint8_t pin_btns[] = {PIN_BTN_1, PIN_BTN_2, PIN_BTN_3};
  interaction_utils::Buttons * buttons = new interaction_utils::Buttons(pin_btns, 3);
  LiquidCrystal_I2C * lcd = new LiquidCrystal_I2C(0x27,16,2);
  at24c32::Interface * eeprom = new at24c32::Interface(0x50, 3, 2);

  Serial.begin(9600);
  lcd->init();
  lcd->backlight();
  lcd->noAutoscroll();
  lcd->setCursor(0, 0);

  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Press button to");
  lcd->setCursor(0, 1);
  lcd->print("start test");
  buttons->wait_first_press();

  // Test writing
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Writing test...");
  String text = "Hello, hello I'm at a place called Vertigo";
  for (at24c32::addr_t i = 0; i < text.length(); i++) {
    if (i < text.length()) {
      eeprom->send_word(i, text[i]);
    } else {
      eeprom->send_word(i, 0x00);
    }
  }

  // Test addressed word reading
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Addre reading");
  lcd->setCursor(0, 1);
  lcd->print("test...");
  for (at24c32::addr_t i = 0; i < at24c32::MEM_LEN; i++) {
    at24c32::word_t word = eeprom->get_word(i);
    Serial.write(word);
  }

  // Test word reading
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Reading test...");
  for (at24c32::addr_t i = 0; i < at24c32::MEM_LEN; i++) {
    at24c32::word_t word = eeprom->get_word();
    Serial.write(word);
  }

  // Test addressed sequential reading
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Addre sequential");
  lcd->setCursor(0, 1);
  lcd->print("test...");
  eeprom->init_sequential_read(0x000);
  for (at24c32::addr_t i = 0; i < at24c32::MEM_LEN; i++) {
    at24c32::word_t word = eeprom->get_next_word();
    Serial.write(word);
  }
  eeprom->end_sequential_read();

  // Test sequential reading
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Seq reading");
  lcd->setCursor(0, 1);
  lcd->print("test...");
  eeprom->init_sequential_read();
  for (at24c32::addr_t i = 0; i < at24c32::MEM_LEN; i++) {
    at24c32::word_t word = eeprom->get_next_word();
    Serial.write(word);
  }
  eeprom->end_sequential_read();

  Serial.end();
}
