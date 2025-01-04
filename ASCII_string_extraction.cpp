#include<fstream>
#include<iostream>
#include<cctype>
#include<string>
using namespace std;
//function which performs ASCII extraction from file
void extract_ascii(string filename){
    ifstream file(filename, ios::binary);
    if(!file){
        cerr<<"Error opening file for ascii extraction\n";
        return;
    }
    char ch;
    cout<<"____________________________________________________\n";
    cout<<"ASCII Extraction: \n";
    while(file.get(ch)){
        if(isprint(ch)){
            cout<<ch;
        }
        else{
            cout<<"\n";
        }
    }
}
int main(int argc, char *argv[]){
    extract_ascii(argv[1]);
    return 0;
}