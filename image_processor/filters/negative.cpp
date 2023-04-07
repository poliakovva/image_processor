#include "negative.h"

void NegativeFilter::Negative(Image& image) {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float new_red = 1 - image.GetPixel(x, y).GetRed();
            float new_green = 1 - image.GetPixel(x, y).GetGreen();
            float new_blue = 1 - image.GetPixel(x, y).GetBlue();
            image.SetPixel(x, y, Color(new_red, new_green, new_blue));
        }
    }
    std::cout << "-neg is successful" << std::endl;
}
