#include "cmd_handler.h"

std::vector<FilterDescriptor> CmdHandler::ParseArgs(int cnt, char** argv) {
    std::vector<FilterDescriptor> req_filters;
    while (cnt > 0) {
        std::string filter_name = ++(*argv);
        ++argv;
        --cnt;
        std::vector<std::string> params;
        while (cnt > 0 && **argv != '-') {
            params.push_back(*argv++);
            --cnt;
        }
        req_filters.push_back({filter_name, params, params.size()});
    }

    return req_filters;
}
