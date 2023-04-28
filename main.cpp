#include <iostream>
#include "image.h"
#include "params.h"

int main() {
    std::string imageFilePath = "../images/color/Lenna.bmp";
    bip::Image<unsigned char> img = bip::imread<unsigned char>(imageFilePath);
    bip::imwrite("../images/out/Lenna.png", img, dataType::uint8_);
}
