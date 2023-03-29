#pragma once
#include "base.h"
#include "../structures/pixel.h"
#include "../structures/matrix.h"

class GsFilter : public Filter {
public:
    matrix<NormalizedPixel>& Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) override;

    const double r_coef = 0.299;
    const double g_coef = 0.587;
    const double b_coef = 0.114;
};
