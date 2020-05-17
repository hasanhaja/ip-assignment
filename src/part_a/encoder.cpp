//
// Created by Hasan on 17/05/20.
//

#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * TODO Function should include creating directories if it does not exist.
 * TODO
 */

//int process_cmd_line(int argc, char* argv[]);
auto debug_cmd_line_args(const char * carrier, const char * message, const char * encoded) -> void;
auto encode(cv::Mat carrier, cv::Mat message) -> cv::Mat;
/**
 * Part A encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
 * Part A decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
 */
auto a_encoder_main(int argc, char* argv[]) -> int {
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
    cv::Mat message = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);

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

    auto encoded = encode(carrier, message);

    // Processing complete.

    // Output
    try {
        image_write_result = cv::imwrite(encoded_des, encoded);
    } catch (const cv::Exception& cv_ex) {
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
auto process_cmd_line(int argc, char* argv[]) -> int {
    std::cout << "Processing..." << std::endl;

    return 0;
}

auto debug_cmd_line_args(const char * carrier, const char * message, const char * encoded) -> void {
    std::cout << "Carrier: " << carrier << "\nMessage: " << message << "\nEncoded: " << encoded << std::endl;
}

/**
 * TODO What about the overflow?
 *
 * @param carrier
 * @param message
 * @return
 */
auto encode(cv::Mat carrier, cv::Mat message) -> cv::Mat {
    cv::Mat encoded;

    // convert message to binary
    // TODO: cv::THRESH_BINARY or cv::THRESH_BINARY_INV?
    cv::threshold(message, message, 0, 1, cv::THRESH_BINARY);

    encoded = carrier + message;

    return encoded;
}