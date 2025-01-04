#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

// function which applies caesar shift
string caesarEncrypt(const string& data, int shift) {
    string result;
    for (char c : data) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            result += (c - base + shift) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

// function which encrypts data into image
void embedData(const string& imageFile, const string& outputImage, const string& fileData, int skipPixels, int startColumn, int shift) {
    cv::Mat image = cv::imread(imageFile, cv::IMREAD_COLOR);
    if (image.empty()) {
        cerr << "Error: Could not open image file.\n";
        return;
    }

    string encryptedData = caesarEncrypt(fileData, shift); // applys caesar shift using input
    encryptedData += '\0'; // appends null terminator to mark the end of data

    int dataIdx = 0;
    int bitCount = 0;

    for (int i = 0; i < image.rows; ++i) {
        for (int j = startColumn; j < image.cols && dataIdx < encryptedData.size(); j += skipPixels) {
            cv::Vec3b& pixel = image.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3 && dataIdx < encryptedData.size(); ++k) { // iterates over B,G,R
                pixel[k] = (pixel[k] & ~1) | ((encryptedData[dataIdx] >> (7 - bitCount)) & 1);
                ++bitCount;
                if (bitCount == 8) {
                    bitCount = 0;
                    ++dataIdx;
                }
            }
        }
    }

    cv::imwrite(outputImage, image);
    cout << "File data successfully embedded into " << outputImage << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        cerr << "Usage: " << argv[0] << " <input_image> <output_image> <input_file> <skip_pixels> <start_column> <cipher_shift>\n";
        return 1;
    }

    string imageFile = argv[1];
    string outputImage = argv[2];
    string inputFile = argv[3];
    int skipPixels = stoi(argv[4]);
    int startColumn = stoi(argv[5]);
    int cipherShift = stoi(argv[6]);

    ifstream file(inputFile);
    if (!file) {
        cerr << "Error: Could not open input file.\n";
        return 1;
    }
    string fileData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    embedData(imageFile, outputImage, fileData, skipPixels, startColumn, cipherShift);
    return 0;
}
