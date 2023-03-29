#pragma once

#include <cstdint>
struct Pixel {
    uint8_t b = 0;
    uint8_t g = 0;
    uint8_t r = 0;
};

struct NormalizedPixel {
    double r = 0;
    double g = 0;
    double b = 0;
};
