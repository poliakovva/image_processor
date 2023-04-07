#include "image_reader.h"

Image Processor::Read(const std::string &path) const {
    Image image;
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "The file could not be opened\n" << std::endl;
        return image;
    }
    unsigned char file_header[FILE_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);

    unsigned char info_header[INFORMATION_HEADER_SIZE];
    f.read(reinterpret_cast<char *>(info_header), INFORMATION_HEADER_SIZE);

    if ((file_header[0] != 'B') || (file_header[1] != 'M')) {
        std::cout << "Wrong file format(not .bmp)\n" << std::endl;
        f.close();
        return image;
    }

    image.SetFileSize(file_header[2] + (file_header[FILE_INDEX_3] << MOVE_8) + (file_header[FILE_INDEX_4] << MOVE_16) +
                      (file_header[FILE_INDEX_5] << MOVE_24));

    image.SetWidth(info_header[WIDTH_INDEX_4] + (info_header[WIDTH_INDEX_5] << MOVE_8) +
                   (info_header[WIDTH_INDEX_6] << MOVE_16) + (info_header[WIDTH_INDEX_7] << MOVE_24));
    image.SetHeight(info_header[HEIGHT_INDEX_8] + (info_header[HEIGHT_INDEX_9] << MOVE_8) +
                    (info_header[HEIGHT_INDEX_10] << MOVE_16) + (info_header[HEIGHT_INDEX_11] << MOVE_24));

    const int padding_amount = static_cast<int>((4 - ((image.GetWidth() * 3) % 4)) % 4);

    ColorMatrix image_matrix;
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        std::vector<Color> line;
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            unsigned char color[3];

            f.read(reinterpret_cast<char *>(color), 3);

            float blue = static_cast<float>(color[0]) / COLOR_DEV;
            float green = static_cast<float>(color[1]) / COLOR_DEV;
            float red = static_cast<float>(color[2]) / COLOR_DEV;

            Color pixel(red, green, blue);
            line.push_back(pixel);
        }
        image_matrix.push_back(line);
        f.ignore(padding_amount);
    }

    image.SetColorMatrix(image_matrix);
    f.close();
    std::cout << path << " opening is successful" << std::endl;

    return image;
}

void Processor::Export(const Image &image, const std::string &path) const {
    if (image.GetFileSize()) {
        std::ofstream f;
        f.open(path, std::ios::out | std::ios::binary);

        if (!f.is_open()) {
            std::cout << "Opening failed\n" << std::endl;
            return;
        }
        unsigned char bmp_pad[3] = {0, 0, 0};
        const int padding_amount = static_cast<int>((4 - ((image.GetWidth() * 3) % 4)) % 4);

        unsigned char file_header[FILE_HEADER_SIZE];

        file_header[0] = 'B';
        file_header[1] = 'M';
        size_t file_size = image.GetFileSize();
        size_t width = image.GetWidth();
        size_t height = image.GetHeight();

        file_header[FILE_INDEX_2] = file_size;
        file_header[FILE_INDEX_3] = file_size >> MOVE_8;
        file_header[FILE_INDEX_4] = file_size >> MOVE_16;
        file_header[FILE_INDEX_5] = file_size >> MOVE_24;

        for (int i = SPARE_INDEX_6; i <= SPARE_INDEX_13; ++i) {
            file_header[i] = 0;
        }
        file_header[INFO_IND_10] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;

        unsigned char info_header[INFORMATION_HEADER_SIZE];
        info_header[0] = INFORMATION_HEADER_SIZE;
        info_header[1] = 0;
        info_header[SPARE_INDEX_2] = 0;
        info_header[SPARE_INDEX_3] = 0;

        info_header[WIDTH_INDEX_4] = width;
        info_header[WIDTH_INDEX_5] = width >> MOVE_8;
        info_header[WIDTH_INDEX_6] = width >> MOVE_16;
        info_header[WIDTH_INDEX_7] = width >> MOVE_24;

        info_header[HEIGHT_INDEX_8] = height;
        info_header[HEIGHT_INDEX_9] = height >> MOVE_8;
        info_header[HEIGHT_INDEX_10] = height >> MOVE_16;
        info_header[HEIGHT_INDEX_11] = height >> MOVE_24;

        info_header[SPARE_INDEX_12] = 1;
        info_header[SPARE_INDEX_13] = 0;

        info_header[BITS] = BPP;

        for (int i = SPARE_INDEX_15; i <= SPARE_INDEX_39; ++i) {
            info_header[i] = 0;
        }
        f.write(reinterpret_cast<char *>(file_header), FILE_HEADER_SIZE);
        f.write(reinterpret_cast<char *>(info_header), INFORMATION_HEADER_SIZE);

        for (int y = 0; y < image.GetHeight(); ++y) {
            for (int x = 0; x < image.GetWidth(); ++x) {
                unsigned char red = static_cast<unsigned char>(image.GetPixel(x, y).GetRed() * COLOR_DEV);
                unsigned char green = static_cast<unsigned char>(image.GetPixel(x, y).GetGreen() * COLOR_DEV);
                unsigned char blue = static_cast<unsigned char>(image.GetPixel(x, y).GetBlue() * COLOR_DEV);

                unsigned char color[3] = {blue, green, red};

                f.write(reinterpret_cast<char *>(color), 3);
            }
            f.write(reinterpret_cast<char *>(bmp_pad), padding_amount);
        }
        f.close();
        std::cout << "File saved to " << path << std::endl;
    }
}
