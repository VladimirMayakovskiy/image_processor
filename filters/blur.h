#pragma once
#include "base.h"

class BlurFilter : public Filter {
public:
    explicit BlurFilter(double sigma);
    matrix<NormalizedPixel> &Apply(matrix<NormalizedPixel> &norm_px_arr, matrix<Pixel> &px_arr) override;

private:
    double sigma_ = 0;
    double sigma_2_ = 0;
    double coeff_ = 0;
    ssize_t radius_ = 0;
    std::vector<double> kernel_;
};