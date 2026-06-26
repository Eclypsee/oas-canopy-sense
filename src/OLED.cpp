#include "OLED.h"

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ OLED_RST);

void OLED_init(){
    pinMode(VEXT_PIN, OUTPUT);
    digitalWrite(VEXT_PIN, LOW); 
    delay(100);
    u8x8.begin(); 
    u8x8.setContrast(255); 
}
void OLED_writeText(const char* t, uint8_t yoffset, const uint8_t* font) {
    u8x8.clearDisplay();
    u8x8.setFont(font);
    u8x8.drawString(0, yoffset, t);
}