
#include "edge.h"
#include "grayscale.h"

const std::vector<double> EdgeFilter::KERNEL({0, -1, 0, -1, 4, -1, 0, -1, 0});

EdgeFilter::EdgeFilter(double threshold) : threshold_(threshold) {
}

matrix<NormalizedPixel>& EdgeFilter::Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) {
    GsFilter gs;
    gs.Apply(norm_px_arr, px_arr);

    ssize_t width = norm_px_arr.GetColsCnt();
    ssize_t height = norm_px_arr.GetRowsCnt();
    ssize_t k_rad_y = 1;
    ssize_t k_rad_x = 1;
    matrix<NormalizedPixel> arr(height, width);
    for (ssize_t y = 0; y < height; ++y) {
        for (ssize_t x = 0; x < width; ++x) {
            arr(y, x) = {0, 0, 0};
            for (ssize_t dy = -k_rad_y, i = 0; dy <= k_rad_y; ++dy) {
                for (ssize_t dx = -k_rad_x; dx <= k_rad_x; ++dx, ++i) {
                    arr(y, x).r += norm_px_arr.At(y + dy, x + dx).r * KERNEL[i];
                }
            }
            arr(y, x) = arr(y, x).r > threshold_ ? NormalizedPixel{1, 1, 1} : NormalizedPixel{0, 0, 0};
            px_arr(y, x) = {static_cast<uint8_t>(arr(y, x).b * UINT8_MAX),
                            static_cast<uint8_t>(arr(y, x).g * UINT8_MAX),
                            static_cast<uint8_t>(arr(y, x).r * UINT8_MAX)};
        }
    }
    norm_px_arr = arr;
    return norm_px_arr;
}