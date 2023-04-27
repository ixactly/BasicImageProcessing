//
// Created by 森智希 on 2023/04/28.
//

#include "image.h"

// constructor
template<typename T>
Image<T>::Image(int width, int height, int channel)
        : width_(width), height_(height), channel_(channel), data_(new T[width * height * channel]) {}

// destructor
template<typename T>
Image<T>::~Image() = default;

// move-constructor
template<typename T>
Image<T>::Image(Image&& other) noexcept
        : width_(other.width_), height_(other.height_), channel_(other.channel_), data_(std::move(other.data_))
{
    other.width_ = 0;
    other.height_ = 0;
    other.channel_ = 0;
}

// move-assignment
template<typename T>
Image<T>& Image<T>::operator=(Image&& other) noexcept
{
    if (this != &other) {
        width_ = other.width_;
        height_ = other.height_;
        channel_ = other.channel_;
        data_ = std::move(other.data_);
        other.width = 0;
        other.height = 0;
        other.channel = 0;
    }
    return *this;
}


