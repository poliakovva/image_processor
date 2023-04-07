#include "weight_matrix.h"
#include "grayscale.h"

const float EDGE_CF = 4.0;
class EdgeFilter : public WeightMatrix {
    std::vector<std::vector<float>> edge_matrix_ = {{0.0, -1.0, 0.0}, {-1.0, EDGE_CF, -1.0}, {0.0, -1.0, 0.0}};

public:
    void Edge(Image& image, const float threshold) const;
};
