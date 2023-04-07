#include "../image/image.h"

class CropFilter {
    size_t crop_width_ = 0;
    size_t crop_height_ = 0;

public:
    explicit CropFilter(const size_t width, const size_t height);
    void Crop(Image& image) const;
};
