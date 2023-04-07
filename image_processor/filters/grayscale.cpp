#include "grayscale.h"

void GrayscaleFilter::Grayscale(Image& image) const {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float new_red = R_SCALE * image.GetPixel(x, y).GetRed();
            float new_green = G_SCALE * image.GetPixel(x, y).GetGreen();
            float new_blue = B_SCALE * image.GetPixel(x, y).GetBlue();
            float new_color = std::min(1.0f, std::max(0.0f, (new_red + new_green + new_blue)));
            image.SetPixel(x, y, Color(new_color, new_color, new_color));
        }
    }
    std::cout << "-gs is successful" << std::endl;
}
