//
// Created by Hasan on 17/05/20.
//

#ifndef IP_ASSIGNMENT_PARTD_ENCODER_CPP
#define IP_ASSIGNMENT_PARTD_ENCODER_CPP


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
* Part D encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
* Part D decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
*/
auto d_encoder_main(int argc, char *argv[]) -> int {
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

    cv::Mat_<cv::Vec3b> carrier = cv::imread(carrier_name, cv::IMREAD_COLOR);
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
                  "ERROR: The carrier and the encoded are not the same size." << carrier.size() << " " << message.size()
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

    // Shuffles the message
    std::shuffle(indices.begin(), indices.end(), gen);

    // for a 2X2 mat will have a 0, 1, 2, 3
    auto encoded = carrier.clone();

    auto shuffled_message = message.clone();

//    std::cout << "Cloned" << std::endl;

    for (int i = 0; i < shuffled_message.total(); i++) {
        auto mes_iter = shuffled_message.begin();
        auto ind_iter = indices.begin();

        std::advance(mes_iter, i);
        auto& current = *mes_iter;

        std::advance(ind_iter, i);

        mes_iter = shuffled_message.begin();
        std::advance(mes_iter, *ind_iter);

        auto& new_val = *mes_iter;

        std::swap(current, new_val);

    }

//    std::cout << "Shuffled" << std::endl;

    for (int i = 0; i < shuffled_message.total(); i++) {
//        for (auto bgr: {0,1,2}) {
//
//
//        }
//        std::cout << "Here" << std::endl;
        auto mes_iter = shuffled_message.begin();
        auto enc_iter = encoded.begin();

        std::advance(mes_iter, i);
        auto& cur_mes = *mes_iter;

        std::advance(enc_iter, i);
        auto& cur_enc = (*enc_iter)[0];

        if (cur_enc != 255) {
            if (cur_mes == 0) {
                cur_enc += 1;
            } else {
                cur_enc += 0;
            }
        }
    }

//    for (auto& pixel: message) {
//        for (auto bgr: {0, 1, 2}) {
//            // value at location
//            auto index_in_encoded = (encoded.begin() + indices[index]);
//            auto& encoded_pixel_ptr = (*index_in_encoded)[bgr];
//
//            if (encoded_pixel_ptr != 255) {
//                if (pixel == 0) {
//                    encoded_pixel_ptr += 1;
//                } else {
//                    encoded_pixel_ptr += 0;
//                }
//            }
//        }
//
//        index++;
//    }

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

#endif // IP_ASSIGNMENT_PARTD_ENCODER_CPP
