#include "Executor.h"
#include "string"
#include "../processor/image_reader.h"

bool IsNumber(std::string& string) {
    for (const char& letter : string) {
        if (!isdigit(letter)) {
            return false;
        }
    }
    return true;
}

bool IsFloat(std::string& string) {
    if (string[0] == '-') {
        string = string.substr(1, string.size() - 1);
    }
    size_t dot_counter = 0;
    for (const char& letter : string) {
        if (letter == '.') {
            dot_counter += 1;
            if (dot_counter > 1) {
                return false;
            }
        }
    }

    for (const char& letter : string) {
        if (!(isdigit(letter) || letter == '.')) {
            return false;
        }
    }
    return true;
}

Executor::Executor(int argc, char** argv) {
    if (argc == 1) {
        Help();
    } else if (argc == 2) {
        std::cout << "Output file not specified, nothing done \n"
                     "hint: Add the path to output file after input file path"
                  << std::endl;
    } else {
        try {
            const std::string input = static_cast<std::string>(argv[1]);
            const std::string output = static_cast<std::string>(argv[2]);
            if (".bmp" != input.substr(input.size() - 4, 4)) {
                throw std::invalid_argument("ERROR: Wrong input file format");
            }

            if (".bmp" != output.substr(output.size() - 4, 4)) {
                throw std::invalid_argument("ERROR: Wrong output file format");
            }
            Processor processor;
            Image image = processor.Read(input);
            if (image.GetFileSize() == 0) {
                throw std::invalid_argument("ERROR: Wrong file size");
            }

            for (size_t i = 3; i < argc; ++i) {
                std::string filter = static_cast<std::string>(argv[i]);
                if (filter[0] != '-') {
                    throw std::invalid_argument("ERROR: Wrong filter name");
                } else if (filter == "-crop") {
                    if (argc - i <= 2) {
                        throw std::invalid_argument("ERROR: No filter arguments given");
                    }
                    ExecuteCrop(image, argv, i);
                    i += 2;
                } else if (filter == "-gs") {
                    ExecuteGrayscale(image);
                } else if (filter == "-neg") {
                    ExecuteNegative(image);
                } else if (filter == "-sharp") {
                    ExecuteSharp(image);
                } else if (filter == "-edge") {
                    if (argc - i <= 1) {
                        throw std::invalid_argument("ERROR: No filter arguments given");
                    }
                    ExecuteEdge(image, argv, i);
                    i += 1;
                } else if (filter == "-blur") {
                    if (argc - i <= 1) {
                        throw std::invalid_argument("ERROR: No filter arguments given");
                    }
                    ExecuteGauss(image, argv, i);
                    i += 1;
                } else {
                    throw std::invalid_argument("ERROR: Unknown command: " + filter);
                }
            }
            processor.Export(image, output);
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
}
void Executor::Help() const {
    std::cout << "\n\nImage Processor\n\n"
                 ""
                 "Format of args:"
                 "     ./image_processor input.bmp output.bmp -filter1 arg1 arg2\n"
                 "These are common commands used in various situations:\n"
                 "    -crop [width] [height]       Crop the photo\n"
                 "    -grayscale                   Grayscale filter\n"
                 "    -neg                         Negative filter\n"
                 "    -sharp                       Sharpening filter\n"
                 "    -edge [threshold]            Crop the photo\n"

              << std::endl;
}
void Executor::ExecuteCrop(Image& image, char** argv, size_t i) {
    std::string width_string = static_cast<std::string>(argv[i + 1]);
    std::string height_string = static_cast<std::string>(argv[i + 2]);

    if (!IsNumber(width_string) || !IsNumber(height_string)) {
        throw std::invalid_argument("ERROR: Filter argument is not numeric");
    }
    int64_t width = std::stoi(width_string);
    int64_t height = std::stoi(height_string);

    if (width < 0 || height < 0) {
        throw std::invalid_argument("ERROR: Filter argument is negative");
    }
    CropFilter crop(width, height);
    crop.Crop(image);
}
void Executor::ExecuteGrayscale(Image& image) {
    GrayscaleFilter gs;
    gs.Grayscale(image);
}
void Executor::ExecuteNegative(Image& image) {
    NegativeFilter neg;
    neg.Negative(image);
}
void Executor::ExecuteSharp(Image& image) {
    SharpeningFilter sharp;
    sharp.Sharpening(image);
}
void Executor::ExecuteEdge(Image& image, char** argv, size_t i) {
    std::string threshold_string = static_cast<std::string>(argv[i + 1]);
    if (!IsFloat(threshold_string)) {
        throw std::invalid_argument("ERROR: Filter argument is not float");
    }
    float threshold = std::stof(threshold_string);

    EdgeFilter edge;
    edge.Edge(image, threshold);
}
void Executor::ExecuteGauss(Image& image, char** argv, size_t i) {
    std::string sigma_string = static_cast<std::string>(argv[i + 1]);
    if (!IsFloat(sigma_string)) {
        throw std::invalid_argument("ERROR: Filter argument is not float");
    }
    float sigma = std::stof(sigma_string);

    GaussFilter gauss;
    gauss.Gauss(image, sigma);
}
