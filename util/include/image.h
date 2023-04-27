//
// Created by 森智希 on 2023/04/28.
//

#ifndef IMAGEPROCESSING_IMAGE_H
#define IMAGEPROCESSING_IMAGE_H

#include<memory>
#include<cstring>

template<typename T>
class Image {
public:
    Image(int w, int h, int c);
    Image(Image&& other) noexcept;
    Image& operator=(Image&& other) noexcept;
    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;
    ~Image();

private:
    int width_;
    int height_;
    int channel_;
    std::unique_ptr<T[]> data_;
};

#endif //IMAGEPROCESSING_IMAGE_H
