//
// Created by 森智希 on 2023/04/28.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H

#include <memory>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "params.h"

namespace bip {
    template<typename T>
    class Image {
    public:
        const int cols;
        const int rows;
        const int dims;

        Image(int width, int height, int channel) : cols(width), rows(height), dims(channel),
                                                    data_(new T[width * height * channel]) {};

        Image(Image &&other) noexcept: cols(other.cols), rows(other.rows), dims(other.dims),
                                       data_(std::move(other.data_)) {};

        Image &operator=(Image &&other) noexcept {
            if (this != &other) {
                cols = other.cols;
                rows = other.rows;
                dims = other.dims;
                data_ = std::move(other.data_);
            }
            return *this;
        };

        Image(const Image &) = delete;

        Image &operator=(const Image &) = delete;

        ~Image() = default;

        T &operator()(int x, int y, int c) {
            return data_[c + x * dims + y * cols * dims];
        }

        const T &operator()(int x, int y, int c) const {
            return data_[c + x * dims + y * cols * dims];
        }

    private:
        std::unique_ptr<T[]> data_;
    };

    template<typename T>
    Image<T> imread(const std::string &path) {
        cv::Mat cv_img = cv::imread(path, cv::IMREAD_UNCHANGED);

        // 画像形式によって処理を分ける
        int step = (int) cv_img.step;

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
            const T *r_raw = cv_img.data;
            const T *g_raw = cv_img.data + 1;
            const T *b_raw = cv_img.data + 2;

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
        return img;
    }

    template<typename T>
    void imwrite(const std::string &path, const Image<T> &img, dataType type) {
        cv::Mat cv_img;
        int dims = img.dims;
        if (dims == 1) {
            cv_img = cv::Mat(img.rows, img.cols, (int)type + (dims-1) * 8);
            for (int y = 0; y < img.rows; y++) {
                for (int x = 0; x < img.cols; x++) {
                    cv_img.at<T>(y, x) = static_cast<T>(img(x, y, 0));
                }
            }
        } else if (dims == 3) {
            cv_img = cv::Mat(img.rows, img.cols, (int)type + (dims-1) * 8);
            for (int y = 0; y < img.rows; y++) {
                for (int x = 0; x < img.cols; x++) {
                    cv_img.at<cv::Vec3b>(y, x)[0] = static_cast<T>(img(x, y, 2));
                    cv_img.at<cv::Vec3b>(y, x)[1] = static_cast<T>(img(x, y, 1));
                    cv_img.at<cv::Vec3b>(y, x)[2] = static_cast<T>(img(x, y, 0));
                }
            }
        } else if (dims == 4) {
            cv_img = cv::Mat(img.rows, img.cols, (int)type + (dims-1) * 8);
            for (int y = 0; y < img.rows; y++) {
                for (int x = 0; x < img.cols; x++) {
                    cv_img.at<cv::Vec4b>(y, x)[0] = static_cast<T>(img(x, y, 2));
                    cv_img.at<cv::Vec4b>(y, x)[1] = static_cast<T>(img(x, y, 1));
                    cv_img.at<cv::Vec4b>(y, x)[2] = static_cast<T>(img(x, y, 0));
                    cv_img.at<cv::Vec4b>(y, x)[3] = static_cast<T>(img(x, y, 3));
                }
            }
        }
        cv::imwrite(path, cv_img);
    }


}
#endif //IMAGEPROCESSING_IMAGE_H
