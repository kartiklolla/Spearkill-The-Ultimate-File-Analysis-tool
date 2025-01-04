#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>

using namespace std;

void runFileAnalysis(const string& filename) {
    system(("./file_type " + filename).c_str());
    system(("./ASCII_string_extraction " + filename).c_str());
}

void runHexDump(const string& filename) {
    system(("./hexdump " + filename).c_str());
}


void runLsbAnalysis(const string& filename, const string& outFile) {
    cout << "Running LSB analysis on: " << filename << endl;
    system(("./lsb_datdecry00 " + filename + " " + outFile).c_str());
}

void runPasswordCracking(const string& hashFile) {
    cout << "Running password cracking on: " << hashFile << endl;
    system(("./password_crack " + hashFile).c_str());
}

void runCustomEncryption(const string& imgFile, const string& outFile, const string& txtFile, int skipPixels, int startColumn, int shift) {
    cout << "Encrypting data into image: " << imgFile << endl;
    system(("./lsb_customencrypt " + imgFile + " " + outFile + " " + txtFile + " " +
            to_string(skipPixels) + " " + to_string(startColumn) + " " + to_string(shift))
               .c_str());
}

void runCustomDecryption(const string& imgFile, const string& outFile, int skipPixels, int startColumn, int shift) {
    cout << "Decrypting data from image: " << imgFile << endl;
    system(("./lsb_customdecrypt " + imgFile + " " + outFile + " " + to_string(skipPixels) + " " +
            to_string(startColumn) + " " + to_string(shift))
               .c_str());
}

void printSpearkillArt() {
    cout << "\033[92m";
    cout << R"(
   _____ ____  _________    ____  __ __ ______    __ 
  / ___// __ \/ ____/   |  / __ \/ //_//  _/ /   / / 
  \__ \/ /_/ / __/ / /| | / /_/ / ,<   / // /   / /  
 ___/ / ____/ /___/ ___ |/ _, _/ /| |_/ // /___/ /___
/____/_/   /_____/_/  |_/_/ |_/_/ |_/___/_____/_____/
                                                     
)";
    cout << "\033[39m";
}

void displayIntroMessage() {
    cout << "Welcome to Spearkill! The Ultimate File Analysis, Data Hiding, and Password Cracking Tool\n";
    cout << "------------------------------------------------------------\n";
    cout << "Run the tool with specific options to analyze files, hide data, or crack passwords.\n";
    cout << "------------------------------------------------------------\n";
    cout << "Use 'spearkill --help' to see all available commands and options.\n";
}

void displayHelpMessage() {
    cout << R"(
Usage: spearkill [OPTIONS] <filename>
Options:
  -a,  <filename>       Perform file analysis.
  -x,  <filename>       Performs hexdump
  -l,  <filename>       Perform LSB data decryption.
  -p,  <hashfile>       Perform password cracking.
  -e,  <args>           Encrypt data into an image.
                                  Args: <image_file> <output_image> <text_file> <skip_pixels> <start_column> <shift>
  -d,  <args>           Decrypt data from an image.
                                  Args: <image_file> <skip_pixels> <start_column> <shift>
  -h, --help                     Display this help message.

Examples:
  spearkill -a file           Analyze a file.
  spearkill -x file           Makes hexdump.
  spearkill -l image.png output.txt         Perform LSB data decryption on an image.
  spearkill -p hashes.txt         Crack passwords from a hash file.
  spearkill -e img.png out.png secret.txt 2 10 3
                                  Encrypt data into an image.
  spearkill -d img.png output.txt 2 10 3     Decrypt data from an image.
)";
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printSpearkillArt();
        displayIntroMessage();
        return 0;
    }

    struct option longOptions[] = {
        {"analyze", required_argument, nullptr, 'a'},
	{"hexdump", required_argument, nullptr, 'x'},
        {"lsb", required_argument, nullptr, 'l'},
        {"password", required_argument, nullptr, 'p'},
        {"encrypt", required_argument, nullptr, 'e'},
        {"decrypt", required_argument, nullptr, 'd'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0}};
    
    int option;
    while ((option = getopt_long(argc, argv, "a:x:l:p:e:d:h", longOptions, nullptr)) != -1) {
        switch (option) {
            case 'a':
                runFileAnalysis(optarg);
                break;
	    case 'x':
                runHexDump(optarg);
                break;	
            case 'l':
		if (argc < 4) {
                    cerr << "Error: Insufficient arguments for lsb analysis.\n";
                    return 1;
		}
                runLsbAnalysis(argv[2], argv[3]);
                break;
            case 'p':
                runPasswordCracking(optarg);
                break;
            case 'e':
                if (argc < 8) {
                    cerr << "Error: Insufficient arguments for encryption.\n";
                    return 1;
                }
                runCustomEncryption(argv[2], argv[3], argv[4], stoi(argv[5]), stoi(argv[6]), stoi(argv[7]));
                break;
            case 'd':
                if (argc < 7) {
                    cerr << "Error: Insufficient arguments for decryption.\n";
                    return 1;
                }
                runCustomDecryption(argv[2], argv[3], stoi(argv[4]), stoi(argv[5]), stoi(argv[6]));
                break;
            case 'h':
                displayHelpMessage();
                return 0;
            default:
                cerr << "Invalid option. Use --help for usage instructions.\n";
                return 1;
        }
    }

    return 0;
}
