#pragma once
#include "../image/image.h"

const float R_SCALE = 0.299f;
const float G_SCALE = 0.586f;
const float B_SCALE = 0.114f;

class GrayscaleFilter {
public:
    void Grayscale(Image& image) const;
};
