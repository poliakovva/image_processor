#pragma once
#include "../image/image.h"

class WeightMatrix {
public:
    void MatrixFilter(Image& image, const std::vector<std::vector<float>>& matrix) const;
};
