
#include "weight_matrix.h"
void WeightMatrix::MatrixFilter(Image& image, const std::vector<std::vector<float>>& matrix) const {
    ColorMatrix color_matrix(image.GetHeight(), std::vector<Color>(image.GetWidth(), Color()));

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            Color cur_color;
            for (int64_t i : {-1, 0, 1}) {
                int64_t cur_x = std::max<int64_t>(x + i, 0);
                cur_x = std::min<int64_t>(cur_x, static_cast<int64_t>(image.GetWidth() - 1));
                for (int64_t j : {-1, 0, 1}) {
                    int64_t cur_y = std::max<int64_t>(y + j, 0);
                    cur_y = std::min<int64_t>(cur_y, static_cast<int64_t>(image.GetHeight() - 1));
                    float cf = matrix[j + 1][i + 1];
                    cur_color.SetRed(cur_color.GetRed() + (image.GetPixel(cur_x, cur_y).GetRed() * cf));
                    cur_color.SetGreen(cur_color.GetGreen() + (image.GetPixel(cur_x, cur_y).GetGreen() * cf));
                    cur_color.SetBlue(cur_color.GetBlue() + (image.GetPixel(cur_x, cur_y).GetBlue() * cf));
                }
            }
            cur_color.SetRed(std::min<float>(1.0f, std::max<float>(0.0f, cur_color.GetRed())));
            cur_color.SetGreen(std::min<float>(1.0f, std::max<float>(0.0f, cur_color.GetGreen())));
            cur_color.SetBlue(std::min<float>(1.0f, std::max<float>(0.0f, cur_color.GetBlue())));
            color_matrix[y][x] = cur_color;
        }
    }
    image.SetColorMatrix(color_matrix);
}
