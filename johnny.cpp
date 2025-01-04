#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void crackPassword(const string& hashFile, const string& wordlist = "") {
    string command;
    
    if (!wordlist.empty()) {
        command = "john --wordlist=" + wordlist + " " + hashFile;
    } else {
        command = "john --incremental " + hashFile;
    }

    cout << "Executing: " << command << endl;

    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error: John the Ripper execution failed!" << endl;
    } else {
        cout << "John the Ripper has completed execution. Check the output above for cracked passwords." << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <hash_file> [wordlist]" << endl;
        return 1;
    }

    string hashFile = argv[1];
    string wordlist = (argc == 3) ? argv[2] : "";

    if (hashFile.empty()) {
        cerr << "Error: Hash file is required." << endl;
        return 1;
    }

    crackPassword(hashFile, wordlist);

    return 0;
}

