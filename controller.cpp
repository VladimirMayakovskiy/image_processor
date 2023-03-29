#include "controller.h"
#include <iostream>

int Controller::Start(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "build/image_processor [input_file] [output_file] [params..]" << std::endl;
        std::cout << "Available filters:\n"
                     "\t[-gs]  Grayscale filter\n"
                     "\t[-neg]  Negative filter\n"
                     "\t[-sharp]  Sharpening\n"
                     "\t[-edge] [threshold]  Edge Detection\n"
                     "\t[-crop] [width, height]  Crop Image\n"
                     "\t[-blur] [sigma]  Gaussian Blur\n"
                     "\t[-motion]  Motion filter"
                  << std::endl;
        return 0;
    }
    if (argc <= 2) {
        throw std::logic_error("Error: no output files received.");
    }
    std::string ifile_name = *argv++;
    std::string ofile_name = *argv++;
    std::vector<FilterDescriptor> filters = CmdHandler::ParseArgs(argc - 3, argv);
    Pipeline pipeline(filters);
    ImageHandler img_handler;
    img_handler.Prepare(ifile_name);
    pipeline.ApplyAll(img_handler.GetNormalizedMatrix(), img_handler.GetPixelMatrix());
    img_handler.CreateBmpFile(ofile_name);
    return 0;
}
