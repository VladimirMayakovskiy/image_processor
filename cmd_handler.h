#pragma once

#include "structures/filter_descriptor.h"
class CmdHandler {
public:
    static std::vector<FilterDescriptor> ParseArgs(int cnt, char** argv);
};
