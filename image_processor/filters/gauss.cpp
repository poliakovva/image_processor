#include "gauss.h"

void GaussFilter::Gauss(Image& image, const float sigma) {

    int64_t dist = std::ceil((CONST_GAUSS * std::abs(sigma)) / DEV);

    ColorMatrix matrix1(image.GetHeight(), std::vector<Color>(image.GetWidth()));
    ColorMatrix matrix2(image.GetHeight(), std::vector<Color>(image.GetWidth()));

    double cf1 = sqrt(1 / (2 * PI * sigma * sigma));

    std::vector<float> cf_vector;

    for (int64_t i = -dist; i <= dist; ++i) {
        cf_vector.push_back(static_cast<float>(cf1 * std::exp((static_cast<double>(-i * i)) / (2 * sigma * sigma))));
    }

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t i = -dist; i <= dist; ++i) {
            int64_t y1 = std::max<int64_t>(y + i, 0);
            y1 = std::min<int64_t>(y1, static_cast<int64_t>(image.GetHeight()) - 1);
            for (int64_t x = 0; x < image.GetWidth(); ++x) {
                matrix1[y][x] = matrix1[y][x] + image.GetPixel(x, y1) * cf_vector[i + dist];
            }
        }
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            for (int64_t i = -dist; i <= dist; ++i) {
                int64_t x1 = std::max<int64_t>(x + i, 0);
                x1 = std::min<int64_t>(x1, static_cast<int64_t>(image.GetWidth()) - 1);
                matrix2[y][x] = matrix2[y][x] + matrix1[y][x1] * cf_vector[i + dist];
            }
        }
    }

    image.SetColorMatrix(matrix2);

    std::cout << "-blur is successful" << std::endl;
}
