#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;

// function to perform casear decryption
string caesarDecrypt(const string& data, int shift) {
    string result;
    for (char c : data) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            result += (c - base - shift + 26) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

// This function extracts data from the image provided
string extractData(const string& imageFile, int skipPixels, int startColumn) {
    cv::Mat image = cv::imread(imageFile, cv::IMREAD_COLOR);
    if (image.empty()) {
        cerr << "Error: Could not open image file.\n";
        return "";
    }

    string hiddenData;
    char currentChar = 0;
    int bitCount = 0;

    for (int i = 0; i < image.rows; ++i) {
        for (int j = startColumn; j < image.cols; j += skipPixels) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(i, j);
            for (int k = 0; k < 3; ++k) { // iteration over B, G, R is done
                currentChar = (currentChar << 1) | (pixel[k] & 1);
                ++bitCount;
                if (bitCount == 8) {
                    if (currentChar == '\0') return hiddenData; // the last of data is returned
                    hiddenData += currentChar;
                    currentChar = 0;
                    bitCount = 0;
                }
            }
        }
    }

    return hiddenData;
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        cerr << "Usage: " << argv[0] << " <input_image> <output_file> <skip_pixels> <start_column> <shift>\n";
        return 1;
    }

    string imageFile = argv[1];
    string outputFile = argv[2];
    int skipPixels = stoi(argv[3]);
    int startColumn = stoi(argv[4]);
    int shift = stoi(argv[5]);

    string extractedData = extractData(imageFile, skipPixels, startColumn);
    string decryptedData = caesarDecrypt(extractedData, shift); // reverse casear cipher with shift provided in input

    ofstream file(outputFile);
    if (!file) {
        cerr << "Error: Could not create output file.\n";
        return 1;
    }
    file << decryptedData;
    cout << "Extracted data successfully saved to " << outputFile << "\n";

    return 0;
}
