//
// Created by Hasan on 18/05/20.
//

#ifndef IP_ASSIGNMENT_PARTC_NOISE_GENERATOR_CPP
#define IP_ASSIGNMENT_PARTC_NOISE_GENERATOR_CPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <random>

auto hash(const char* password) -> unsigned long;
auto combine_noise_and_carrier(cv::Mat carrier, const char* password) -> cv::Mat;

auto c_main(int argc, char *argv[]) -> int {

    // Process command line inputs and handle errors
    if (argc < 4) {
        std::cerr <<
                  "Not enough arguments into the program.\nThe usage is program.exe <carrier_dir> <message_dir> <encoded_des>"
                  << std::endl;

        return -1;
    }

    auto carrier_name = argv[2];
    auto output_name = argv[3];

    auto image_write_result = false;

    std::cout << "Processing encoder..." << std::endl;

    cv::Mat_<uchar> carrier = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);
//    cv::Mat_<uchar> message = cv::imread(message_name, cv::IMREAD_GRAYSCALE);

    if (carrier.empty()) {
        std::cerr <<
                  "ERROR: Either carrier image nor message image does not exist."
                  << std::endl;
        return -1;
    }

    std::cout << "SUCCESS: Images loaded successfully" << std::endl;

    // Check if the images are the same size

//    if (carrier.size() != message.size()) {
//        std::cerr <<
//                  "ERROR: The carrier and the message are not the same size."
//                  << std::endl;
//        return -1;
//    }

    std::cout << "SUCCESS: Images compatible." << std::endl;

    // Setup complete

    auto output = combine_noise_and_carrier(carrier, "password");


    try {
        image_write_result = cv::imwrite(output_name, output);
    } catch (const cv::Exception &cv_ex) {
        std::cerr << "ERROR: Encoded image write failed.\n" << cv_ex.what() << std::endl;
    }

    if (image_write_result) {
        std::cout << "SUCCESS: Encoded image written successfully." << std::endl;
    } else {
        std::cerr << "ERROR: Encoded image write failed." << std::endl;
    }

    return image_write_result ? 0 : 1;
}

/**
 * TODO check for overflow
 * @param carrier
 * @param password
 * @return
 */
auto combine_noise_and_carrier(cv::Mat carrier, const char* password) -> cv::Mat {

    auto output = carrier.clone();

    cv::threshold(carrier, carrier, 64, 128, cv::THRESH_BINARY_INV);

    // TODO prompt for password
//    auto password = "password";
    auto random_seed = (unsigned int) hash(password);

    // A vector the same size as the message
    std::vector<uchar> indices(carrier.cols * carrier.rows);

    for (int i = 0; i < carrier.rows; i++) {
        for (int j = 0; j < carrier.cols; j++) {
            indices.push_back(carrier.at<uchar>(i, j));
        }
    }

    // convert the message to a vector for shuffling

    std::mt19937 gen;
    gen.seed(random_seed);

    // Shuffles the message
    std::shuffle(indices.begin(), indices.end(), gen);

    int index = 0;

    // Convert back to matrix
    for (int i = 0; i < carrier.rows; i++) {
        for (int j = 0; j < carrier.cols; j++) {
            carrier.at<uchar>(i, j) = indices[index];
            index++;
        }
    }

    output += carrier;

    return output;
}

#endif //IP_ASSIGNMENT_PARTB_ENCODER_CPP