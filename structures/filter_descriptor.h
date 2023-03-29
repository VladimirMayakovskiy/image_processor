#pragma once

#include <string>
#include <vector>
struct FilterDescriptor {
    std::string name_;
    std::vector<std::string> params_;
    size_t params_cnt_ = 0;
};
