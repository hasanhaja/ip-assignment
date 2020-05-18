//
// Created by Hasan on 17/05/20.
//

#ifndef IP_ASSIGNMENT_PARTA_DECODER_CPP
#define IP_ASSIGNMENT_PARTA_DECODER_CPP

#include <iostream>
#include <opencv2/opencv.hpp>


/**
 * Part A encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
 * Part A decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
 */

//namespace decoder {

auto debug_cmd_line_args(const char * carrier, const char * message, const char * encoded) -> void;
auto a_decode(cv::Mat carrier, cv::Mat encoded) -> cv::Mat_<uchar>;
auto debug_image(const char* image_name, const cv::Mat& image) -> void;

auto a_decoder_main(int argc, char* argv[]) -> int {
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

    cv::Mat carrier = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);
    cv::Mat encoded = cv::imread(encoded_name, cv::IMREAD_GRAYSCALE);

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
                  "ERROR: The carrier and the encoded are not the same size."
                  << std::endl;
        return -1;
    }

    std::cout << "SUCCESS: Images compatible." << std::endl;

    // Setup complete

    // Processing

    auto decoded = a_decode(carrier, encoded);

    // Processing complete.

    // Output
    try {
        image_write_result = cv::imwrite(decoded_des, decoded);
    } catch (const cv::Exception& cv_ex) {
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
//    auto process_cmd_line(int argc, char* argv[]) -> int {
//        std::cout << "Processing..." << std::endl;
//
//        return 0;
//    }

//auto debug_cmd_line_args(const char * carrier, const char * message, const char * encoded) -> void {
//    std::cout << "Carrier: " << carrier << "\nMessage: " << message << "\nEncoded: " << encoded << std::endl;
//}
//
//auto debug_image(const char* image_name, const cv::Mat& image) -> void {
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
auto a_decode(cv::Mat carrier, cv::Mat encoded) -> cv::Mat_<uchar> {

    // uchar so it cannot be negative and so it isn't over 8bits
    cv::Mat decoded = cv::Mat_<uchar>::ones(carrier.size());

    debug_image("Original test", encoded);

    decoded -= encoded - carrier;
    debug_image("Decoded test", decoded*255);

    // Invert it
    cv::threshold(decoded, decoded, 0, 1, cv::THRESH_BINARY_INV);
    debug_image("Inverse Decoded test", decoded*255);

    decoded *= 255;
    return decoded;
}
//}


#endif // IP_ASSIGNMENT_PARTA_DECODER_CPP