#include "crop.h"
CropFilter::CropFilter(const size_t width, const size_t height) : crop_width_(width), crop_height_(height) {
}
void CropFilter::Crop(Image& image) const {
    size_t cur_width = (crop_width_ <= image.GetWidth()) ? crop_width_ : image.GetWidth();
    size_t cur_height = (crop_height_ <= image.GetHeight()) ? crop_height_ : image.GetHeight();
    ColorMatrix cur_matrix = image.GetColorMatrix();
    std::reverse(cur_matrix.begin(), cur_matrix.end());
    cur_matrix.resize(cur_height);
    for (std::vector<Color>& vec : cur_matrix) {
        vec.resize(cur_width);
    }
    std::reverse(cur_matrix.begin(), cur_matrix.end());
    image.SetColorMatrix(cur_matrix);
    std::cout << "-crop is successful" << std::endl;
}
