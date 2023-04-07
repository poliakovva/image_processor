#include "image.h"
#include "../processor/image_reader.h"
Color::Color(const float red, const float green, const float blue) {
    red_ = red;
    green_ = green;
    blue_ = blue;
}

float Color::GetRed() const {
    return red_;
}
float Color::GetGreen() const {
    return green_;
}
float Color::GetBlue() const {
    return blue_;
}
void Color::SetRed(const float color) {
    red_ = color;
}
void Color::SetGreen(const float color) {
    green_ = color;
}
void Color::SetBlue(const float color) {
    blue_ = color;
}
Image::Image() {
}
Image::Image(const size_t width, const size_t height) {
    width_ = width;
    height_ = height;
}

size_t Image::GetHeight() const {
    return height_;
}
size_t Image::GetWidth() const {
    return width_;
}
void Image::SetWidth(const size_t width) {
    width_ = width;
}
void Image::SetHeight(const size_t height) {
    height_ = height;
}

ColorMatrix Image::GetColorMatrix() const {
    return color_matrix_;
}
void Image::SetColorMatrix(const ColorMatrix& color_matrix) {
    color_matrix_ = color_matrix;
    height_ = color_matrix.size();
    width_ = color_matrix[0].size();
    const int padding_amount = static_cast<int>((4 - ((width_ * 3) % 4)) % 4);

    file_size_ = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + height_ * width_ * 3 + padding_amount * height_;
}
const Color& Image::GetPixel(const size_t x, const size_t y) const {
    return color_matrix_[y][x];
}
void Image::SetPixel(const size_t x, const size_t y, const Color& color) {
    color_matrix_[y][x] = color;
}
size_t Image::GetFileSize() const {
    return file_size_;
}
void Image::SetFileSize(const size_t file_size) {
    file_size_ = file_size;
}

Color Color::operator*(const float cf) const {
    return Color(this->red_ * cf, this->green_ * cf, this->blue_ * cf);
}

Color Color::operator+(const Color& color) const {
    return Color(this->red_ + color.red_, this->green_ + color.green_, this->blue_ + color.blue_);
}

Color Color::operator-(const Color& color) const {
    return Color(this->red_ - color.red_, this->green_ - color.green_, this->blue_ - color.blue_);
}
