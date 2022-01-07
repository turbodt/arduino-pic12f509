
#include <application/screen/display_configuration_values.hpp>

namespace screen {

  namespace display_configuration_values {

    const String display_mclr(pic12f509::word_t const & conf_word) {
      switch (pic12f509::get_mclr_selection(conf_word)) {
        case pic12f509::CONF_MCLRE_GP3:
          return "GP3";
        case pic12f509::CONF_MCLRE_MCLR:
          return "Master Clear";
      }
      return "Unknown";
    }

    const String display_cp(pic12f509::word_t const & conf_word) {
      return pic12f509::is_code_proctection_enabled(conf_word)
        ? "Enabled"
        : "Disabled";
    }

    const String display_wdt(pic12f509::word_t const & conf_word) {
      return pic12f509::is_watchdog_timer_enabled(conf_word)
        ? "Enabled"
        : "Disabled";
    }

    const String display_osc(pic12f509::word_t const & conf_word) {
      switch (pic12f509::get_oscillator_selection(conf_word)) {
        case pic12f509::CONF_OSC_SEL_LP:
          return "LP Oscillator";
        case pic12f509::CONF_OSC_SEL_XP:
          return "XP Oscillator";
        case pic12f509::CONF_OSC_SEL_EXTRC:
          return "External RC";
        case pic12f509::CONF_OSC_SEL_INTOSC:
          return "INTOSC";
      }
      return "Unknown";
    }

  }

  void display_configuration_values::set_conf_word(pic12f509::word_t const & conf_word) {
    input::pic->init();
    input::pic->send_command(pic12f509::CMD_LOAD_DATA);
    input::pic->send_word(conf_word);
    input::pic->send_command(pic12f509::CMD_BEGIN_PROGRAMMING);
    input::pic->send_command(pic12f509::CMD_END_PROGRAMMING);
    input::pic->end();
  }

  void display_configuration_values::edit_mclr(pic12f509::word_t & conf_word) {
    pic12f509::word_t new_conf_word = conf_word;
    bool exit_loop = false;
    while (!exit_loop) {
      input::lcd->clear();
      input::lcd->setCursor(1, 0);
      input::lcd->print("MCLR Selection");

      String value_str = display_mclr(new_conf_word);
      input::lcd->setCursor((17 - value_str.length()) / 2, 1);
      input::lcd->print(value_str);
      input::lcd->setCursor(0, 1);
      input::lcd->print('<');
      input::lcd->setCursor(15, 1);
      input::lcd->print('>');

      uint8_t button = input::buttons->wait_first_press();

      if (button == 1 || button == 2) {
        switch (pic12f509::get_mclr_selection(new_conf_word)) {
          case pic12f509::CONF_MCLRE_GP3:
            new_conf_word &= ~pic12f509::CONF_MCLRE_MASK;
            new_conf_word |= pic12f509::CONF_MCLRE_MCLR;
            break;
          case pic12f509::CONF_MCLRE_MCLR:
            new_conf_word &= ~pic12f509::CONF_MCLRE_MASK;
            new_conf_word |= pic12f509::CONF_MCLRE_GP3;
            break;
        }
      } else if (button == 0) {
        exit_loop = true;
        display_configuration_values::set_conf_word(new_conf_word);
        conf_word = new_conf_word;
      }
    }

  }

  void display_configuration_values::edit_cp(pic12f509::word_t & conf_word) {
    pic12f509::word_t new_conf_word = conf_word;
    bool exit_loop = false;
    while (!exit_loop) {
      input::lcd->clear();
      input::lcd->setCursor(2, 0);
      input::lcd->print("Code Protect");

      String value_str = display_cp(new_conf_word);
      input::lcd->setCursor((17 - value_str.length()) / 2, 1);
      input::lcd->print(value_str);
      input::lcd->setCursor(0, 1);
      input::lcd->print('<');
      input::lcd->setCursor(15, 1);
      input::lcd->print('>');

      uint8_t button = input::buttons->wait_first_press();

      if (button == 1 || button == 2) {
        if (pic12f509::is_code_proctection_enabled(new_conf_word)) {
            new_conf_word &= ~pic12f509::CONF_CODE_PROTECTION_MASK;
            new_conf_word |= pic12f509::CONF_CODE_PROTECTION_OFF;
        } else {
            new_conf_word &= ~pic12f509::CONF_CODE_PROTECTION_MASK;
            new_conf_word |= pic12f509::CONF_CODE_PROTECTION_ON;
        }
      } else if (button == 0) {
        exit_loop = true;
        display_configuration_values::set_conf_word(new_conf_word);
        conf_word = new_conf_word;
      }
    }
  }

  void display_configuration_values::edit_wdt(pic12f509::word_t & conf_word) {
    pic12f509::word_t new_conf_word = conf_word;
    bool exit_loop = false;
    while (!exit_loop) {
      input::lcd->clear();
      input::lcd->setCursor(1, 0);
      input::lcd->print("Watchdog Timer");

      String value_str = display_wdt(new_conf_word);
      input::lcd->setCursor((17 - value_str.length()) / 2, 1);
      input::lcd->print(value_str);
      input::lcd->setCursor(0, 1);
      input::lcd->print('<');
      input::lcd->setCursor(15, 1);
      input::lcd->print('>');

      uint8_t button = input::buttons->wait_first_press();

      if (button == 1 || button == 2) {
        if (pic12f509::is_watchdog_timer_enabled(new_conf_word)) {
            new_conf_word &= ~pic12f509::CONF_WDTE_MASK;
            new_conf_word |= pic12f509::CONF_WDTE_OFF;
        } else {
            new_conf_word &= ~pic12f509::CONF_WDTE_MASK;
            new_conf_word |= pic12f509::CONF_WDTE_ON;
        }
      } else if (button == 0) {
        exit_loop = true;
        display_configuration_values::set_conf_word(new_conf_word);
        conf_word = new_conf_word;
      }
    }
  }

  void display_configuration_values::edit_osc(pic12f509::word_t & conf_word) {
    pic12f509::word_t new_conf_word = conf_word;
    bool exit_loop = false;
    while (!exit_loop) {
      input::lcd->clear();
      input::lcd->setCursor(3, 0);
      input::lcd->print("Oscillator");

      String value_str = display_osc(new_conf_word);
      input::lcd->setCursor((17 - value_str.length()) / 2, 1);
      input::lcd->print(value_str);
      input::lcd->setCursor(0, 1);
      input::lcd->print('<');
      input::lcd->setCursor(15, 1);
      input::lcd->print('>');

      uint8_t button = input::buttons->wait_first_press();

      if (button == 2) {
        switch (pic12f509::get_oscillator_selection(new_conf_word)) {
          case pic12f509::CONF_OSC_SEL_LP:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_EXTRC;
            break;
          case pic12f509::CONF_OSC_SEL_XP:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_LP;
            break;
          case pic12f509::CONF_OSC_SEL_INTOSC:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_XP;
            break;
          case pic12f509::CONF_OSC_SEL_EXTRC:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_INTOSC;
            break;
        }
      } else if (button == 1) {
        switch (pic12f509::get_oscillator_selection(new_conf_word)) {
          case pic12f509::CONF_OSC_SEL_LP:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_XP;
            break;
          case pic12f509::CONF_OSC_SEL_XP:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_INTOSC;
            break;
          case pic12f509::CONF_OSC_SEL_INTOSC:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_EXTRC;
            break;
          case pic12f509::CONF_OSC_SEL_EXTRC:
            new_conf_word &= ~pic12f509::CONF_OSC_SEL_MASK;
            new_conf_word |= pic12f509::CONF_OSC_SEL_LP;
            break;
        }
      } else if (button == 0) {
        exit_loop = true;
        display_configuration_values::set_conf_word(new_conf_word);
        conf_word = new_conf_word;
      }
    }
  }

  void display_configuration_values::run() {

    pic12f509::word_t conf_word = 0;

    input::lcd->clear();
    input::lcd->setCursor(0, 0);
    input::lcd->print("Reading...");

    input::pic->init();

    // Conf word is only readable before first CMD_INCREMENT_ADDRESS
    input::pic->send_command(pic12f509::CMD_READ_DATA);
    conf_word = input::pic->get_word();
    input::pic->end();

    // display info
    const uint8_t num_pages = 4;
    String headers[] = {
      "MCLR Selection",
      "Code Protect",
      "Watchdog Timer",
      "Oscillator"
    };
    const String (* funcs[])(const pic12f509::word_t &) = {
      display_mclr,
      display_cp,
      display_wdt,
      display_osc
    };
    void (* actions[])(pic12f509::word_t &) = {
      edit_mclr,
      edit_cp,
      edit_wdt,
      edit_osc
    };

    bool exit_loop = false;
    uint8_t page_index = 0;
    while (!exit_loop) {
      input::lcd->clear();
      input::lcd->setCursor(0, 0);
      input::lcd->print('<');
      input::lcd->setCursor(15, 0);
      input::lcd->print('>');

      if (page_index == num_pages) {
        input::lcd->setCursor(6, 0);
        input::lcd->print("Back");
      } else {
        input::lcd->setCursor((16 - headers[page_index].length()) / 2, 0);
        input::lcd->print(headers[page_index]);

        String value_str = funcs[page_index](conf_word);
        input::lcd->setCursor((17 - value_str.length()) / 2, 1);
        input::lcd->print(value_str);
      }

      uint8_t button = input::buttons->wait_first_press();

      if (button == 1) {
        page_index = (page_index -1 + num_pages + 1) % (num_pages + 1);
      } else if (button == 2) {
        page_index = (page_index +1) % (num_pages + 1);
      } else if (button != 0) {
        // this should never happen
      } else if (page_index == num_pages) {
        // go back
        exit_loop = true;
      } else {
        // edit value
        actions[page_index](conf_word);
      }
    }
  }
}
