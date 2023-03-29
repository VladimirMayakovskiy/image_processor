#include "controller.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        Controller controller;
        ++argv;
        controller.Start(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Error:\t" << e.what() << std::endl;
    }
    return 0;
}
