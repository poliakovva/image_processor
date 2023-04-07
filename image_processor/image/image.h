#pragma once

#include <vector>
#include <fstream>
#include <iostream>

class Color {
    float red_ = 0;
    float green_ = 0;
    float blue_ = 0;

public:
    float GetRed() const;
    float GetGreen() const;
    float GetBlue() const;

    void SetRed(const float color);
    void SetGreen(const float color);
    void SetBlue(const float color);
    explicit Color(const float red = 0, const float green = 0, const float blue = 0);

    Color operator*(const float cf) const;
    Color operator+(const Color& color) const;
    Color operator-(const Color& color) const;
};

using ColorMatrix = std::vector<std::vector<Color>>;

class Image {
    size_t file_size_ = 0;
    size_t width_ = 0;
    size_t height_ = 0;
    ColorMatrix color_matrix_ = {};

public:
    Image();
    explicit Image(const size_t width, const size_t height);

    size_t GetWidth() const;
    size_t GetHeight() const;
    void SetWidth(const size_t width);
    void SetHeight(const size_t width);

    ColorMatrix GetColorMatrix() const;
    void SetColorMatrix(const ColorMatrix& color_matrix);
    const Color& GetPixel(const size_t x, const size_t y) const;
    void SetPixel(const size_t x, const size_t y, const Color& color);

    size_t GetFileSize() const;
    void SetFileSize(const size_t file_size);
};
