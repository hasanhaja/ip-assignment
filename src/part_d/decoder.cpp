//
// Created by Hasan on 17/05/20.
//

#ifndef IP_ASSIGNMENT_PARTD_DECODER_CPP
#define IP_ASSIGNMENT_PARTD_DECODER_CPP


#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <random>
#include <vector>
#include <algorithm>

/**
 * TODO Function should include creating directories if it does not exist.
 * TODO
 */

//namespace encoder {


//int process_cmd_line(int argc, char* argv[]);
auto debug_cmd_line_args(const char *carrier, const char *message, const char *encoded) -> void;
auto debug_image(const char* image_name, const cv::Mat& image) -> void;
auto a_decode(cv::Mat carrier, cv::Mat message) -> cv::Mat_<uchar>;
auto hash(const char* password) -> unsigned long;

/**
* Part A encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
* Part A decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
*/
auto d_decoder_main(int argc, char *argv[]) -> int {
// Process command line inputs and handle errors
    if (argc < 5) {
        std::cerr <<
                  "Not enough arguments into the program.\nThe usage is program.exe <carrier_dir> <message_dir> <encoded_des>"
                  << std::endl;

        return -1;
    }

    auto carrier_name = argv[2];
    auto encoded_name = argv[3];
    auto decoded_des = argv[4];

    auto image_write_result = false;

    std::cout << "Processing decoder..." << std::endl;

    debug_cmd_line_args(carrier_name, encoded_name, decoded_des);

    cv::Mat_<cv::Vec3b> carrier = cv::imread(carrier_name, cv::IMREAD_COLOR);
    cv::Mat_<cv::Vec3b> encoded = cv::imread(encoded_name, cv::IMREAD_COLOR);

    if (carrier.empty() || encoded.empty()) {
        std::cerr <<
                  "ERROR: Either carrier image nor encoded image does not exist."
                  << std::endl;
        return -1;
    }

    std::cout << "SUCCESS: Images loaded successfully" << std::endl;

    // Check if the images are the same size

    if (carrier.size() != encoded.size()) {
        std::cerr <<
                  "ERROR: The carrier and the encoded are not the same size." << carrier.size() << " " << encoded.size()
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
    std::vector<int> indices(encoded.cols * encoded.rows);


    // convert the message to a vector for shuffling

    std::mt19937 gen;
    gen.seed(random_seed);
//    cv::RNG gen(random_seed);

    // Shuffles the message
    std::shuffle(indices.begin(), indices.end(), gen);

    cv::Mat_<uchar> decoded = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);
//    auto carrier_pixel = *(carrier.begin());
//    auto encoded_pixel = *(encoded.begin());

    if (decoded.empty()) {
        std::cerr <<
                  "ERROR: Decoded image cannot be read as grayscale."
                  << std::endl;
        return -1;
    }

    for (int i = 0; i < decoded.total(); i++) {
//        for (auto bgr: {0,1,2}) {
//
//        }

        auto dec_iter = decoded.begin();
        auto enc_iter = encoded.begin();

        std::advance(dec_iter, i);
        auto& cur_dec = *dec_iter;

        std::advance(enc_iter, i);
        auto& cur_enc = (*enc_iter)[0];

        if ((cur_enc - cur_dec) == 1) {
            cur_dec = 0;
        } else {
            cur_dec = 255;
        }
    }

    // Shuffle decoded back
    for (int i = 0; i < decoded.total(); i++) {
        auto dec_iter = decoded.begin();
        auto ind_iter = indices.begin();

        std::advance(dec_iter, i);
        auto& current = *dec_iter;

        std::advance(ind_iter, i);

        dec_iter = decoded.begin();
        std::advance(dec_iter, *ind_iter);

        auto& new_val = *dec_iter;

        std::swap(current, new_val);

    }

    // Processing complete.

    // Output
    try {
        image_write_result = cv::imwrite(decoded_des, decoded);
    } catch (const cv::Exception &cv_ex) {
        std::cerr << "ERROR: Decoded image write failed.\n" << cv_ex.what() << std::endl;
    }

    if (image_write_result) {
        std::cout << "SUCCESS: Decoded image written successfully." << std::endl;
    } else {
        std::cerr << "ERROR: Decoded image write failed." << std::endl;
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
//auto hash(const char* password) -> unsigned long {
//    unsigned long hash = 5381;
//    int c;
//
//    while (c = *password++)
//        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
//
//    return hash;
//}

//}
#endif // IP_ASSIGNMENT_PARTD_DECODER_CPP