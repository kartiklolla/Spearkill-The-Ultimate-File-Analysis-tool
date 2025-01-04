#include<fstream>
#include<iostream>
#include<cctype>
#include<string>
using namespace std;

// Function which performs ASCII extraction from file
void extract_ascii(string filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Error opening file for ASCII extraction\n";
        return;
    }
    char ch;
    cout << "____________________________________________________\n";
    cout << "ASCII Extraction: \n";
    bool has_printable = false;  // To track if we need to print a newline at all
    while (file.get(ch)) {
        if (isprint(ch)) {
            cout << ch;
            has_printable = true;
        } else {
            if (has_printable) {
                cout << "\n";  // Only print a newline if printable characters were printed before
                has_printable = false;
            }
        }
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    extract_ascii(argv[1]);
    return 0;
}

