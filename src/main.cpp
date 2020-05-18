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

    std::string a_encode_flag = "--encode-a";
    std::string a_decode_flag = "--decode-a";

    std::string b_encode_flag = "--encode-b";
    std::string b_decode_flag = "--decode-b";

    std::string d_encode_flag = "--encode-d";
    std::string d_decode_flag = "--decode-d";

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

    if (a_encode_flag.compare(argv[1]) == 0) {
        return a_encoder_main(argc, argv);
    } else if (a_decode_flag.compare(argv[1]) == 0) {
        return a_decoder_main(argc, argv);
    } else if (b_encode_flag.compare(argv[1]) == 0) {
        return b_encoder_main(argc, argv);
    } else if (b_decode_flag.compare(argv[1]) == 0) {
        return b_decoder_main(argc, argv);
    } else if (d_encode_flag.compare(argv[1]) == 0) {
        return d_encoder_main(argc, argv);
    } else if (d_decode_flag.compare(argv[1]) == 0) {
        return d_decoder_main(argc, argv);
    }

    return -1;
}