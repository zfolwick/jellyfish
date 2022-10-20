#include "LiquidCrystal_CI.h"
#ifdef MOCK_PINS_COUNT

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

LiquidCrystal_CI::LiquidCrystal_CI(uint8_t rs, uint8_t rw, uint8_t enable,
                                   uint8_t d0, uint8_t d1, uint8_t d2,
                                   uint8_t d3, uint8_t d4, uint8_t d5,
                                   uint8_t d6, uint8_t d7)
    : LiquidCrystal_Base(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7) {
  init(rs);
}

LiquidCrystal_CI::LiquidCrystal_CI(uint8_t rs, uint8_t enable, uint8_t d0,
                                   uint8_t d1, uint8_t d2, uint8_t d3,
                                   uint8_t d4, uint8_t d5, uint8_t d6,
                                   uint8_t d7)
    : LiquidCrystal_Base(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) {
  init(rs);
}

LiquidCrystal_CI::LiquidCrystal_CI(uint8_t rs, uint8_t rw, uint8_t enable,
                                   uint8_t d0, uint8_t d1, uint8_t d2,
                                   uint8_t d3)
    : LiquidCrystal_Base(rs, rw, enable, d0, d1, d2, d3) {
  init(rs);
}

LiquidCrystal_CI::LiquidCrystal_CI(uint8_t rs, uint8_t enable, uint8_t d0,
                                   uint8_t d1, uint8_t d2, uint8_t d3)
    : LiquidCrystal_Base(rs, enable, d0, d1, d2, d3) {
  init(rs);
}

void LiquidCrystal_CI::init(uint8_t rs) {
  _rs_pin = rs;
  _col = 0;
  _cols = 16;
  _row = 0;
  _rows = 1;
  _autoscroll = false;
  _display = false;
  _cursor = false;
  _blink = false;
  _isInCreateChar = false;
  _lines.clear();
  _lines.resize(_rows);
  for (int character = 0; character < 8; character++) {
    for (int bite = 0; bite < 8; bite++) {
      _customChars[character][bite] = B00000;
    }
  }
  LiquidCrystal_CI::_instances[_rs_pin] = this;
}

void LiquidCrystal_CI::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
  LiquidCrystal_Base::begin(cols, lines, dotsize);
  _col = 0;
  _cols = cols;
  _row = 0;
  _rows = lines;
  _autoscroll = false;
  _display = false;
  _cursor = false;
  _blink = false;
  _isInCreateChar = false;
  _lines.clear();
  _lines.resize(_rows);
}

/********** high level commands, for the user! */
void LiquidCrystal_CI::clear() {
  LiquidCrystal_Base::clear();
  _lines.clear();
  _lines.resize(_rows);
}

void LiquidCrystal_CI::home() {
  LiquidCrystal_Base::home();
  _col = _row = 0;
}

void LiquidCrystal_CI::setCursor(uint8_t col, uint8_t row) {
  LiquidCrystal_Base::setCursor(col, row);
  _col = col;
  _row = row;
}

// Turn the display on/off (quickly)
void LiquidCrystal_CI::noDisplay() {
  LiquidCrystal_Base::noDisplay();
  _display = false;
}
void LiquidCrystal_CI::display() {
  LiquidCrystal_Base::display();
  _display = true;
}

// Turns the underline cursor on/off
void LiquidCrystal_CI::noCursor() {
  LiquidCrystal_Base::noCursor();
  _cursor = false;
}
void LiquidCrystal_CI::cursor() {
  LiquidCrystal_Base::cursor();
  _cursor = true;
}

// Turn on and off the blinking cursor
void LiquidCrystal_CI::noBlink() {
  LiquidCrystal_Base::noBlink();
  _blink = false;
}
void LiquidCrystal_CI::blink() {
  LiquidCrystal_Base::blink();
  _blink = true;
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_CI::scrollDisplayLeft() {
  LiquidCrystal_Base::scrollDisplayLeft();
}
void LiquidCrystal_CI::scrollDisplayRight() {
  LiquidCrystal_Base::scrollDisplayRight();
}

// This is for text that flows Left to Right
void LiquidCrystal_CI::leftToRight() { LiquidCrystal_Base::leftToRight(); }

// This is for text that flows Right to Left
void LiquidCrystal_CI::rightToLeft() { LiquidCrystal_Base::rightToLeft(); }

// This will 'right justify' text from the cursor
void LiquidCrystal_CI::autoscroll() {
  LiquidCrystal_Base::autoscroll();
  _autoscroll = true;
}

// This will 'left justify' text from the cursor
void LiquidCrystal_CI::noAutoscroll() {
  LiquidCrystal_Base::noAutoscroll();
  _autoscroll = false;
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_CI::createChar(uint8_t location, uint8_t charmap[]) {
  _isInCreateChar = true;
  LiquidCrystal_Base::createChar(location, charmap);
  _isInCreateChar = false;
  // fill the customChars with the charmap
  for (int line = 0; line < 8; line++) {
    _customChars[location][line] = charmap[line];
  }
}

inline size_t LiquidCrystal_CI::write(uint8_t value) {
  if (!_isInCreateChar) {
    String line = _lines.at(_row);
    int end = _autoscroll ? (_col - 1) : _col;
    while (line.length() <= end) {
      line += ' ';
    }

    if (_autoscroll) {
      for (int i = 0; i < (_col - 1); i++) {
        line.at(i) = line.at(i + 1);
      }
      --_col;
    }

    line.at(_col) = value;
    ++_col;

    _lines.at(_row) = line;
  }
  return LiquidCrystal_Base::write(value);
}

// override lower-level write to capture output
size_t LiquidCrystal_CI::write(const char *buffer, size_t size) {
  return LiquidCrystal_Base::write(buffer, size);
}

// private data and functions to support testing

LiquidCrystal_CI *LiquidCrystal_CI::_instances[MOCK_PINS_COUNT];

#endif
