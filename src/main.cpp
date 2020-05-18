/**
 * @author Hasan Ali <hasanhaja@gmail.com
 *
 * Tested on:
 * @opencv_version 4.2.0
 *
 */

#include <string>
#include <iostream>

auto a_encoder_main(int argc, char* argv[]) -> int;
auto a_decoder_main(int argc, char* argv[]) -> int;

auto b_encoder_main(int argc, char* argv[]) -> int;
auto b_decoder_main(int argc, char* argv[]) -> int;
//
///**
// * TODO Function should include creating directories if it does not exist.
// * TODO changed usage:
//      `mainprog.exe --help` should be the same as the error message
//      `mainprog.exe --encode <carrier_dir> <message_dir> <encoded_des>`
//      `mainprog.exe --encode <carrier_dir> <message_dir> <encoded_des>`
// */
//
auto main(int argc, char* argv[]) -> int {

    std::string encode_flag = "--encode";
    std::string decode_flag = "--decode";

    // TODO print usage
    if (argc < 5) {
        std::cerr <<
                  "Not enough arguments into the program.\nThe usage is program.exe <carrier_dir> <message_dir> <encoded_des>"
                  << std::endl;

        return -1;
    }

    if (encode_flag.compare(argv[1]) == 0) {
        return b_encoder_main(argc, argv);
    } else if (decode_flag.compare(argv[1]) == 0) {
        return b_decoder_main(argc, argv);
    }

    return -1;
}