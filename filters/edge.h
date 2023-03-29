#pragma once
#include "base.h"

class EdgeFilter : public Filter {
public:
    explicit EdgeFilter(double threshold);
    matrix<NormalizedPixel>& Apply(matrix<NormalizedPixel>& norm_px_arr, matrix<Pixel>& px_arr) override;
    static const std::vector<double> KERNEL;

private:
    double threshold_ = 0;
};
