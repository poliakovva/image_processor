#include "../image/image.h"

const int FILE_HEADER_SIZE = 14;
const int INFORMATION_HEADER_SIZE = 40;

const int MOVE_8 = 8;
const int MOVE_16 = 16;
const int MOVE_24 = 24;

const int FILE_INDEX_2 = 2;
const int FILE_INDEX_3 = 3;
const int FILE_INDEX_4 = 4;
const int FILE_INDEX_5 = 5;

const float COLOR_DEV = 255.0f;

const int WIDTH_INDEX_4 = 4;
const int WIDTH_INDEX_5 = 5;
const int WIDTH_INDEX_6 = 6;
const int WIDTH_INDEX_7 = 7;

const int HEIGHT_INDEX_8 = 8;
const int HEIGHT_INDEX_9 = 9;
const int HEIGHT_INDEX_10 = 10;
const int HEIGHT_INDEX_11 = 11;

const int SPARE_INDEX_2 = 2;
const int SPARE_INDEX_3 = 3;
const int SPARE_INDEX_6 = 6;
const int SPARE_INDEX_12 = 12;
const int SPARE_INDEX_13 = 13;
const int SPARE_INDEX_15 = 15;
const int SPARE_INDEX_39 = 39;

const int INFO_IND_10 = 10;

const int BITS = 14;
const int BPP = 24;

class Processor {
public:
    Image Read(const std::string& path) const;
    void Export(const Image& image, const std::string& path) const;
};
