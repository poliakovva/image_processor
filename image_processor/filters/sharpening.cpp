#include "sharpening.h"

void SharpeningFilter::Sharpening(Image& image) const {
    MatrixFilter(image, sharp_matrix_);
    std::cout << "-sharp is successful" << std::endl;
}
