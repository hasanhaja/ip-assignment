/**
 * @author Hasan Ali <hasanhaja@gmail.com
 *
 * Tested on:
 * @opencv_version 4.2.0
 *
 */

int a_encoder_main(int argc, char* argv[]);
int a_decoder_main(int argc, char* argv[]);
//
///**
// * TODO Function should include creating directories if it does not exist.
// * TODO changed usage:
//      `mainprog.exe --help` should be the same as the error message
//      `mainprog.exe --encode <carrier_dir> <message_dir> <encoded_des>`
//      `mainprog.exe --encode <carrier_dir> <message_dir> <encoded_des>`
// */
//
int main(int argc, char* argv[]) {
    auto result = a_encoder_main(argc, argv);
    return result;
}