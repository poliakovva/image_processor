#include "../image/image.h"
#include <cmath>

const float CONST_GAUSS = 6.0f;
const float DEV = 2.0f;
const double PI = acos(-1.0);

class GaussFilter {
public:
    void Gauss(Image& image, const float sigma);
};
