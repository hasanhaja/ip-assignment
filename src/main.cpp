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

auto c_main(int argc, char *argv[]) -> int;

auto d_encoder_main(int argc, char* argv[]) -> int;
auto d_decoder_main(int argc, char* argv[]) -> int;
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
    std::string gen_noise_flag = "--noise";

    // TODO print usage
    if (argc == 4) {
        if (gen_noise_flag.compare(argv[1]) == 0) {
            return c_main(argc, argv);
        } else {
            std::cerr <<
                      "Not enough arguments into the program.\nThe usage is program.exe <carrier_dir> <message_dir> <encoded_des>"
                      << std::endl;
            return -1;
        }
    } else if (argc < 5) {
        std::cerr <<
                  "Not enough arguments into the program.\nThe usage is program.exe <carrier_dir> <message_dir> <encoded_des>"
                  << std::endl;

        return -1;
    }

    if (encode_flag.compare(argv[1]) == 0) {
        return d_encoder_main(argc, argv);
    } else if (decode_flag.compare(argv[1]) == 0) {
        return d_decoder_main(argc, argv);
    }

    return -1;
}