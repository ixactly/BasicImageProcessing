//
// Created by 森智希 on 2023/05/04.
//

#ifndef IMAGEPROCESSING_TONECURVE_H
#define IMAGEPROCESSING_TONECURVE_H

#include "image.h"
#include "params.h"

namespace bip {
    template<typename T>
    void toneCurve(Image<T> &img, double gamma) {
        for (int c = 0; c < img.dims(); c++) {
            for (int x = 0; x < img.cols(); x++) {
                for (int y = 0; y < img.rows(); y++) {
                    img(x, y, c) = static_cast<T>(P_MAX * std::pow(img(x, y, c) / P_MAX, 1.0 / gamma));
                }
            }
        }
    }

    template<typename T>
    void posterize(Image<T> &img, int step) {
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

    template<typename T>
    void pseudoColor(Image<T> &img) {
        if (img.dims() != 1)
            convertToGray(img);

        Image<T> rgb(img.cols(), img.rows(), 3);
        auto r_val = [](double gray_val) -> T {
            if (gray_val < P_MAX / 2.0) {
                return 0.0;
            } else if (gray_val < 3.0 * P_MAX / 4.0) {
                return 4.0 * (gray_val - P_MAX / 2.0);
            } else {
                return P_MAX;
            }
        };
        auto g_val = [](double gray_val) -> T {
            if (gray_val < P_MAX / 4.0) {
                return 4.0 * gray_val;
            } else if (gray_val < 3 * P_MAX / 4.0) {
                return P_MAX;
            } else {
                return 4.0 * (P_MAX - gray_val);
            }
        };
        auto b_val = [](double gray_val) -> T  {
            if (gray_val < P_MAX / 4.0) {
                return P_MAX;
            } else if (gray_val < P_MAX / 2.0) {
                return 4.0 * (P_MAX / 2.0 - gray_val);
            } else {
                return 0.0;
            }
        };

        for (int x = 0; x < img.cols(); x++) {
            for (int y = 0; y < img.rows(); y++) {
                rgb(x, y, 0) = r_val(static_cast<double>(img(x, y, 0)));
                rgb(x, y, 1) = g_val(static_cast<double>(img(x, y, 1)));
                rgb(x, y, 2) = b_val(static_cast<double>(img(x, y, 2)));
            }
        }
        img = std::move(rgb);
    }
}
#endif //IMAGEPROCESSING_TONECURVE_H
