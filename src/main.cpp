#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <pic12f509.interface.hpp>
#include <interaction_utils.hpp>
#include <application.hpp>
#include <at24c32.interface.hpp>

#define PIN_BTN_1 A1
#define PIN_BTN_2 A3
#define PIN_BTN_3 A2
#define PIN_EEPROM_DATA 3
#define PIN_EEPROM_CLOCK 2

#define PIN_DATA 13
#define PIN_CLOCK 12
#define PIN_VDD 11
#define PIN_VPP 10

void application::init() {
  uint8_t pin_btns[] = {PIN_BTN_1, PIN_BTN_2, PIN_BTN_3};
  application::input::buttons = new interaction_utils::Buttons(pin_btns, 3);
  application::input::pic = new pic12f509::Pic12f509Interface(PIN_VPP, PIN_VDD, PIN_CLOCK, PIN_DATA);
  application::input::lcd = new LiquidCrystal_I2C(0x27,16,2);
  application::input::eeprom = new at24c32::Interface(0x50, PIN_EEPROM_DATA, PIN_EEPROM_CLOCK);
}

void setup() {
  Serial.begin(9600);
  Serial.write("---- SETUP ----\n");
  Serial.flush();
  Serial.end();
}

void loop() {
  Serial.begin(9600);
  Serial.write("---- START LOOP ----\n");
  Serial.flush();
  Serial.end();
  application::init();
  application::run();
  application::end();
  Serial.begin(9600);
  Serial.write("---- END ----\n");
  Serial.flush();
  Serial.end();
}
