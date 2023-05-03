//
// Created by 森智希 on 2023/05/04.
//

#ifndef IMAGEPROCESSING_TONECURVE_H
#define IMAGEPROCESSING_TONECURVE_H

#include "image.h"
#include "params.h"

namespace bip {
    template<typename T>
    void toneCurve(bip::Image<T> &img, double gamma) {
        for (int c = 0; c < img.dims; c++) {
            for (int x = 0; x < img.cols; x++) {
                for (int y = 0; y < img.rows; y++) {
                    img(x, y, c) = static_cast<T>(P_MAX * std::pow(img(x, y, c) / P_MAX, 1.0 / gamma));
                }
            }
        }
    }

    template<typename T>
    void posterize(bip::Image<T> &img, int step) {
        auto retPixelVal = [](int step, double pixel_val) {
            int level = (int) (pixel_val * step / P_MAX); // pixel_val / (255.0 / step)
            level = (level == step) ? level - 1 : level;
            // make step function by using int type
            return (P_MAX / (step - 1)) * level;
        };

        for (int c = 0; c < img.dims; c++) {
            for (int x = 0; x < img.cols; x++) {
                for (int y = 0; y < img.rows; y++) {
                    img(x, y, c) = static_cast<T>(retPixelVal(step, img(x, y, c)));
                }
            }
        }
    }
}
#endif //IMAGEPROCESSING_TONECURVE_H
