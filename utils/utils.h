#pragma once

#include <cstdint>

namespace utils {
	class logger;
    struct pixel
    {
        union
        {
            uint32_t n = 0xFF000000;
            struct
            {
                uint8_t r;	uint8_t g;	uint8_t b;	uint8_t a;
            };
        };

        pixel();
        pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
        pixel(uint32_t p);
        enum Mode { NORMAL, MASK, ALPHA, CUSTOM };
    };

	void panic();
}