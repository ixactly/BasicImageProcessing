//
// Created by 森智希 on 2023/04/28.
//
#include "image.h"
#include <string>
#include <opencv2/opencv.hpp>

namespace im {
    template<typename T>
    Image<T> inputImage(std::string path) {
        cv::Mat cv_img = cv::imread(path, cv::IMREAD_UNCHANGED);

        // 画像形式によって処理を分ける
        int step = cv_img.step;

        // 画像の幅と高さを取得する
        int width = cv_img.cols;
        int height = cv_img.rows;
        int channel = cv_img.channels();

        // Image型
        Image<T> img(width, height, channel);

        if (channel == 1) {
            // グレースケール画像の場合
            std::cout << "The input image is grayscale" << std::endl;

        } else if (channel == 3) {
            // RGB画像の場合
            std::cout << "The input image is RGB" << std::endl;
            cv::cvtColor(cv_img, cv_img, cv::COLOR_BGR2RGB);

            // 各チャンネルのrawデータを取得する
            const uchar *r_raw = cv_img.data;
            const uchar *g_raw = cv_img.data + 1;
            const uchar *b_raw = cv_img.data + 2;

            // rawデータを出力する
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    img(x, y, 0) = r_raw[step * y + x * 3]; // Rチャンネル
                    img(x, y, 1) = g_raw[step * y + x * 3]; // Gチャンネル
                    img(x, y, 2) = b_raw[step * y + x * 3]; // Bチャンネル
                }
            }
        } else if (channel == 4) {
            // RGBA画像の場合
            std::cout << "The input image is RGBA" << std::endl;
        }
    }
}
