#ifndef APP_SSD1306_H
#define APP_SSD1306_H

#include "i2c.h"
#include "oled.h"
#include <stdint.h>

#ifdef __cplusplus

class SSD1306_I2C : public OLED<SSD1306_I2C>{
private:
    I2C_HandleTypeDef *hi2c;
    const uint16_t address;

    void sendCmd(uint8_t cmd);

    uint8_t GRAM[8][128] = {};
public:
    static constexpr uint8_t col = 128;
    static constexpr uint8_t page = 8;
    void init();
    void showFrame();
    /**
     * @brief Set a pixel in the GRAM buffer
     * @param x Range 0-127 (GRAM[][x]), begins at top left
     * @param y Range 0-63 (GRAM[y/8][x], bit y%8) begins at top left
     * @param state 1 to set pixel, 0 to clear pixel
     */
    void setPixel(uint8_t x, uint8_t y, uint8_t state);
    /**
     * @brief Clear the GRAM buffer
     * @note This function only clears the GRAM buffer. You need to call showFrame() to update the display after calling this function.
     */
    void clear();
    SSD1306_I2C(I2C_HandleTypeDef *hi2c, uint16_t address = 0x78)
        : hi2c(hi2c), address(address){}
};

#endif /* APP_SSD1306_H */


#endif
