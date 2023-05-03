//
// Created by 森智希 on 2023/05/04.
//

#ifndef IMAGEPROCESSING_TONECURVE_H
#define IMAGEPROCESSING_TONECURVE_H

#include <image.h>
namespace bip {
    template<typename T>
    void toneCurve(bip::Image<T> &img, double gamma) {
        for (int c = 0; c < img.dims; c++) {
            for (int x = 0; x < img.cols; x++) {
                for (int y = 0; y < img.rows; y++) {
                    img(x, y, c) = static_cast<T>(255.0 * std::pow(img(x, y, c) / 255.0, 1.0 / gamma));
                }
            }
        }
    }
}
#endif //IMAGEPROCESSING_TONECURVE_H
