#include "weight_matrix.h"

const float SHARP_CF = 5.0;
class SharpeningFilter : public WeightMatrix {
    std::vector<std::vector<float>> sharp_matrix_ = {{0.0, -1.0, 0.0}, {-1.0, SHARP_CF, -1.0}, {0.0, -1.0, 0.0}};

public:
    void Sharpening(Image& image) const;
};
