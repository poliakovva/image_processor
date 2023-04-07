add_executable(
        image_processor
        image_processor.cpp
        image/image.cpp
        image/image.h

        processor/image_reader.cpp
        processor/image_reader.h
        filters/crop.cpp
        filters/crop.h
        Executor/Executor.cpp
        Executor/Executor.h filters/grayscale.cpp filters/grayscale.h filters/negative.cpp filters/negative.h filters/weight_matrix.cpp filters/weight_matrix.h filters/sharpening.cpp filters/sharpening.h filters/edge_det.cpp filters/edge_det.h filters/gauss.cpp filters/gauss.h)
