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
void debug_cmd_line_args(const char * carrier, const char * message, const char * encoded);

/**
 * Part A encoding: `program.exe <carrier_dir> <message_dir> <encoded_des>`
 * Part A decoding: `program.exe <carrier_dir> <encoded_dir> <decoded_des>`
 */
int a_encoder_main(int argc, char* argv[]) {
    // Process command line inputs and handle errors
    if (argc < 4) {
        std::cerr <<
                  "Not enough arguments into the program.\nThe usage is program.exe <carrier_dir> <message_dir> <encoded_des>"
                  << std::endl;

        return -1;
    }

    auto carrier_name = argv[1];
    auto message_name = argv[2];
    auto encoded_des = argv[3];

    cv::Mat encoded;
    auto image_write_result = false;

    std::cout << "Processing..." << std::endl;

    debug_cmd_line_args(carrier_name, message_name, encoded_des);

    cv::Mat carrier = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);
    cv::Mat message = cv::imread(carrier_name, cv::IMREAD_GRAYSCALE);

    if (carrier.empty() || message.empty()) {
        std::cerr <<
                  "ERROR: Either carrier image nor message image does not exist."
                  << std::endl;
        return -1;
    }

    // Setup complete

    // Processing




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
int process_cmd_line(int argc, char* argv[]) {
    std::cout << "Processing..." << std::endl;

    return 0;
}

void debug_cmd_line_args(const char * carrier, const char * message, const char * encoded) {
    std::cout << "Carrier: " << carrier << "\nMessage: " << message << "\nEncoded: " << encoded << std::endl;
}