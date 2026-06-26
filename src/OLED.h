#ifndef OLED_H
#define OLED_H

#include <U8x8lib.h>

#define OLED_RST 21
#define VEXT_PIN 36

// Use extern here so other files can see it without duplicating it
extern U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8;

void OLED_init();
void OLED_writeText(const char* t, uint8_t yoffset, const uint8_t* font);
#endif