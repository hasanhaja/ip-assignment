//
// Created by Hasan on 17/05/20.
//

#ifndef IP_ASSIGNMENT_PARTB_ENCODER_CPP
#define IP_ASSIGNMENT_PARTB_ENCODER_CPP


#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>

/**
 * TODO Function should include creating directories if it does not exist.
 * TODO
 */

//namespace encoder {


//int process_cmd_line(int argc, char* argv[]);
auto debug_cmd_line_args(const char *carrier, const char *message, const char *encoded) -> void;
auto debug_image(const char* image_name, const cv::Mat& image) -> void;
auto a_encode(cv::Mat carrier, cv::Mat message) -> cv::Mat_<uchar>;
auto hash(const char* password) -> unsigned long;

/**
* Part A encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
* Part A decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
*/
auto b_encoder_main(int argc, char *argv[]) -> int {
    // Process command line inputs and handle errors
    if (argc < 5) {
        std::cerr <<
                  "Not enough arguments into the program.\nThe usage is program.exe <carrier_dir> <message_dir> <encoded_des>"
                  << std::endl;

        return -1;
    }

    auto carrier_name = argv[2];
    auto message_name = argv[3];
    auto encoded_des = argv[4];

    auto image_write_result = false;

    std::cout << "Processing encoder..." << std::endl;

    debug_cmd_line_args(carrier_name, message_name, encoded_des);

    cv::Mat_<uchar> carrier = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);
    cv::Mat_<uchar> message = cv::imread(message_name, cv::IMREAD_GRAYSCALE);

    if (carrier.empty() || message.empty()) {
        std::cerr <<
                  "ERROR: Either carrier image nor message image does not exist."
                  << std::endl;
        return -1;
    }

    std::cout << "SUCCESS: Images loaded successfully" << std::endl;

    // Check if the images are the same size

    if (carrier.size() != message.size()) {
        std::cerr <<
                  "ERROR: The carrier and the message are not the same size."
                  << std::endl;
        return -1;
    }

    std::cout << "SUCCESS: Images compatible." << std::endl;

    // Setup complete

    // Processing

    // TODO prompt for password
    auto password = "password";
    auto random_seed = (unsigned int) hash(password);

    // A vector the same size as the message
    std::vector<int> indices(message.cols * message.rows);

    // Prepopulate the indices vector with values from 0 to indices.size()
    for(int i = 0; i < indices.size(); i++) {
        indices[i] = i;
    }

    // shuffle

    std::mt19937 gen;
    gen.seed(random_seed);
//    cv::RNG gen(random_seed);

    // Shuffles the locations
    std::shuffle(indices.begin(), indices.end(), gen);

    auto shuffled_message = message.clone();

    debug_image("Pre shuffled", shuffled_message);

//    std::cout << "Indices size: " << indices.size() << ", shuffled size: " << shuffled_message.total() << std::endl;

    for (int i = 0; i < shuffled_message.total(); i++) {
        auto mes_iter = shuffled_message.begin();
        auto ind_iter = indices.begin();

        std::advance(mes_iter, i);
        auto& current = *mes_iter;

        std::advance(ind_iter, i);

        // reset it before advancing again
        mes_iter = shuffled_message.begin();
        std::advance(mes_iter, *ind_iter);

        auto& new_val = *mes_iter;

        std::swap(current, new_val);

    }

//    debug_image("First shuffled", shuffled_message);
//
//    auto test_message = shuffled_message.clone();
//
//    for (int i = 0; i < test_message.total(); i++) {
//
//        auto mes_iter = test_message.begin();
//        auto ind_iter = indices.begin();
//
//        std::advance(mes_iter, i);
//        auto& current = *mes_iter;
//
//        std::advance(ind_iter, i);

//        mes_iter = shuffled_message.begin();
//        std::advance(mes_iter, *ind_iter);
//
//        auto& new_val = *mes_iter;
//
//        std::swap(current, new_val);
//    }

//    debug_image("Re-shuffled", test_message);

    auto encoded = a_encode(carrier, shuffled_message);

    // Processing complete.

    // Output
    try {
        image_write_result = cv::imwrite(encoded_des, encoded);
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
 * Taken from http://www.cse.yorku.ca/~oz/hash.html
 * @param str
 * @return
 */
auto hash(const char* password) -> unsigned long {
    unsigned long hash = 5381;
    int c;

    while (c = *password++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

//}
#endif // IP_ASSIGNMENT_PARTB_ENCODER_CPP