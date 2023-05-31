#include <iostream>
#include "image.h"
#include "ContrastTrans.h"
#include "Filtering.h"
#include "params.h"

int main() {
    std::string image_file_path = "../images/mono/Lenna_noise.bmp";
    bip::Image<float> img = bip::imread<float>(image_file_path);
    // bip::toneCurve(img, 0.5);
    // bip::posterize(img, 4);
    // bip::pseudoColor(img);
    // bip::addNoise(img, 20.0);
    bip::totalVariationMinimized(img, 1.0, 1.0, 10);
    // bip::convertToGray(img);

    bip::imwrite("../images/out/Lenna_tv.bmp", img);
}
