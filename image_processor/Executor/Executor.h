#include <iostream>
#include "string"
#include "../image/image.h"
#include "../filters/crop.h"
#include "../filters/negative.h"
#include "../filters/sharpening.h"
#include "../filters/edge_det.h"
#include "../filters/gauss.h"

#include <stdexcept>

class Executor {
public:
    Executor(int argc, char** argv);
    void Help() const;
    void ExecuteCrop(Image& image, char** argv, size_t i);
    void ExecuteGrayscale(Image& image);
    void ExecuteNegative(Image& image);
    void ExecuteSharp(Image& image);
    void ExecuteEdge(Image& image, char** argv, size_t i);
    void ExecuteGauss(Image& image, char** argv, size_t i);
};
