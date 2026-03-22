#ifndef APP_OLED_H
#define APP_OLED_H

#include "font.h"
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct{
    uint8_t x;
    uint8_t y;
}Pointer;

#ifdef __cplusplus
}

template <typename T>
concept OLEDInterface = requires(T& oled) {
    oled.showFrame();
};

template<typename DERIVED>
class OLED {
public:
    OLED() = default;
    void showFrame(){static_cast<DERIVED*>(this)->showFrame();}

    void clear(){static_cast<DERIVED*>(this)->clear();};
    void setPixel(uint8_t x, uint8_t y, uint8_t state){static_cast<DERIVED*>(this)->setPixel(x, y, state);}
    
    /**
     * @brief Display a monochrome bitmap on the OLED screen
     * @param picture Pointer to the bitmap data array
     * @param width Width of the bitmap in bytes (actual pixel width = width * 8)
     * @param height Height of the bitmap in pixels (number of rows)
     * @param ptr Position pointer for the top-left corner of the bitmap
     * @note The bitmap data is stored in row-major order where each byte represents 8 horizontal pixels
     */
    void setPicture(uint8_t* picture, uint8_t width, uint8_t height, Pointer ptr);
    void setChar(char character, Pointer ptr, const Font *font);
    /**
     * @brief Set a string on the OLED screen with pointer tracking
     * @param string String to display (ASCII characters + '\n' for newline)
     * @param ptr Pointer to position, will be updated during operation
     * @param font Font to use for rendering
     * @param rspacing Horizontal spacing between characters
     * @param cspacing Vertical spacing between lines
     * @param backpointer If true (default), returns pointer to original position after operation
     * @attention String must consist of ASCII numbers, alphabets, symbols, spaces; only '\n' is supported for newline
     */
    void setString(const char* string, Pointer *ptr, const Font *font,
        uint8_t rspacing, uint8_t cspacing, bool backpointer = 1);
        /**
     * @brief Set a string on the OLED screen with pointer tracking
     * @param string String to display (ASCII characters + '\n' for newline)
     * @param ptr Pointer to position, will be updated during operation
     * @param font Font to use for rendering
     * @param rspacing Horizontal spacing between characters
     * @param cspacing Vertical spacing between lines
     * @attention String must consist of ASCII numbers, alphabets, symbols, spaces; only '\n' is supported for newline
     */
    void setString(const char* string, Pointer ptr, const Font *font,
        uint8_t rspacing, uint8_t cspacing);
    
};

#ifndef APP_CPP_OLED_OLED_IPP
#include "oled.ipp"
#endif

#endif /* __cplusplus */

#endif /* APP_OLED_H */