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

/**
 * TODO Function should include creating directories if it does not exist.
 * TODO
 */

//namespace encoder {


//int process_cmd_line(int argc, char* argv[]);
auto debug_cmd_line_args(const char *carrier, const char *message, const char *encoded) -> void;
auto debug_image(const char* image_name, const cv::Mat& image) -> void;
auto a_encode(cv::Mat carrier, cv::Mat message) -> cv::Mat;
auto hash(const char* passsword) -> unsigned long;

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

    cv::Mat carrier = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);
    cv::Mat message = cv::imread(message_name, cv::IMREAD_GRAYSCALE);

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

    for (int i = 0; i < message.rows; i++) {
        for (int j = 0; j < message.cols; j++) {
            indices.push_back(message.at<uchar>(i, j));
        }
    }

//    // Prepopulate the indices vector with values from 0 to indices.size()
//    for(int i = 0; i < indices.size(); i++) {
//        indices[i] = i;
//    }

    // convert the message to a vector for shuffling

    std::mt19937 gen;
    gen.seed(random_seed);

    // Shuffles the message
    std::shuffle(indices.begin(), indices.end(), gen);

    int index = 0;

    // Convert back to matrix
    for (int i = 0; i < message.rows; i++) {
        for (int j = 0; j < message.cols; j++) {
            message.at<uchar>(i, j) = indices[index];
            index++;
        }
    }

    auto encoded = a_encode(carrier, message);

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
* # Usage:
*
* To run the program, execute it with: `program.exe <carrier_dir> <output_dir>`
* Part A encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
* Part A decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
*
* Part B encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
* Part B decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
*
* @param argc
* @param argv
*/
//auto process_cmd_line(int argc, char *argv[]) -> int {
//    std::cout << "Processing..." << std::endl;
//
//    return 0;
//}
//
//auto debug_cmd_line_args(const char *carrier, const char *message, const char *encoded) -> void {
//    std::cout << "Carrier: " << carrier << "\nMessage: " << message << "\nEncoded: " << encoded << std::endl;
//}
//
//auto debug_image(const char *image_name, const cv::Mat &image) -> void {
//    cv::namedWindow(image_name, cv::WINDOW_AUTOSIZE);
//
//    cv::imshow(image_name, image);
//
//    cv::waitKey(0);
//}

/**
* TODO What about the overflow?
*
* @param carrier
* @param message
* @return
*/
//auto encode(cv::Mat carrier, cv::Mat message) -> cv::Mat {
//    cv::Mat encoded;
//
//    debug_image("Original test", message);
//
//    // convert message to binary
//    // TODO: cv::THRESH_BINARY or cv::THRESH_BINARY_INV?
////    cv::threshold(message, message, 0, 1, cv::THRESH_BINARY_INV);
//    cv::threshold(message, message, 0, 1, cv::THRESH_BINARY);
//
//    debug_image("Threshold test", message * 255);
//
//    // What is even the point of this?!
////    message = cv::Mat_<uchar>::ones(message.size()) - message;
//
//    // print image
//
//    debug_image("Binary test", message * 255);
//
//    encoded = carrier + message;
//
//    return encoded;
//}

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
#endif // IP_ASSIGNMENT_PARTA_ENCODER_CPP