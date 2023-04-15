#include <filesystem>
#include <stdlib.h>
#include <iostream>

#include "Halide.h"

#include "halide_image_io.h"
using namespace Halide::Tools;

int main(int argc, char *argv[]) {
    std::string img_src = argv[1];
    Halide::Buffer<uint8_t> input = load_image(img_src);

    Halide::Func encoder;

    Halide::Var x, y, c;

    Halide::Expr value = input(x, y, c);

    encoder(x, y, c) = value;

    int destWidth = input.width();
    int destHeight = input.height();
    if (argc >= 3) {
        int iArgWidth = atoi(argv[2]);
        if (iArgWidth > 0) {
            destWidth = atoi(argv[2]);
        }
    }
    if (argc >= 4) {
        int iArgHeight = atoi(argv[3]);
        if (iArgHeight > 0) {
            destHeight = atoi(argv[3]);
        }
    }

    Halide::Buffer<uint8_t> output =
        encoder.realize({destWidth, destHeight, input.channels()});

    std::string dest_filename = "resized_";
    std::filesystem::path fs_path(img_src);
    dest_filename += fs_path.filename().string();

    save_image(output, dest_filename);
    std::cout << dest_filename;
    return 0;
}
