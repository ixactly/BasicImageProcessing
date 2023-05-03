#include <iostream>
#include "image.h"
#include "ContrastTrans.h"
#include "params.h"

int main() {
    std::string image_file_path = "../images/color/Lenna.png";
    bip::Image<uchar> img = bip::imread<uchar>(image_file_path);
    bip::toneCurve(img, 0.5);

    bip::imwrite("../images/out/Lenna_trans.png", img);
}
