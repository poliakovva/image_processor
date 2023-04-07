#include "edge_det.h"

void EdgeFilter::Edge(Image& image, const float threshold) const {
    GrayscaleFilter grayscale;
    grayscale.Grayscale(image);
    MatrixFilter(image, edge_matrix_);
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float red = image.GetPixel(x, y).GetRed();
            if (red > threshold) {
                Color color(1.0, 1.0, 1.0);
                image.SetPixel(x, y, color);
            } else {
                Color color;
                image.SetPixel(x, y, color);
            }
        }
    }
    std::cout << "-edge is successful" << std::endl;
}
