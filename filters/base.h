#pragma once

#include "../structures/pixel.h"
#include "../structures/matrix.h"
class Filter {
public:
    virtual matrix<NormalizedPixel>& Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) = 0;
    virtual ~Filter() = default;
};