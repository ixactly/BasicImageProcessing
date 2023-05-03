#include <iostream>
#include "image.h"
#include "ContrastTrans.h"
#include "params.h"

int main() {
    std::string image_file_path = "../images/color/Lenna.bmp";
    bip::Image<uchar> img = bip::imread<uchar>(image_file_path);
    // bip::toneCurve(img, 0.5);
    // bip::posterize(img, 4);
    // bip::pseudoColor(img);

    bip::imwrite("../images/out/Lenna_col_pseudo.png", img);
}
