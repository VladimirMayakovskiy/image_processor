
#include <cstddef>
#include "grayscale.h"

matrix<NormalizedPixel>& GsFilter::Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) {
    ssize_t rows = norm_px_arr.GetRowsCnt();
    ssize_t cols = norm_px_arr.GetColsCnt();
    for (ssize_t y = 0; y < rows; ++y) {
        for (ssize_t x = 0; x < cols; ++x) {
            NormalizedPixel& px = norm_px_arr(y, x);
            double clr = (r_coef * px.r + g_coef * px.g + b_coef * px.b);
            px = {clr, clr, clr};
            px_arr(y, x) = {static_cast<uint8_t>(px.r * UINT8_MAX), static_cast<uint8_t>(px.r * UINT8_MAX),
                            static_cast<uint8_t>(px.r * UINT8_MAX)};
        }
    }
    return norm_px_arr;
}