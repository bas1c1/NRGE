#include "utils.h"

#include <iostream>

void utils::panic() {
	std::cout << "\n\nABORT!" << std::endl;
	exit(-1);
}

utils::pixel::pixel()
{
    r = 0; g = 0; b = 0; a = 255;
}

utils::pixel::pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    r = red; g = green; b = blue; a = alpha;
}

utils::pixel::pixel(uint32_t p)
{
    n = p;
}