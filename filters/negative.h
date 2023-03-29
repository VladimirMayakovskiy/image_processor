#pragma once
#include "base.h"

class NegativeFilter : public Filter {
public:
    matrix<NormalizedPixel>& Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) override;
};
