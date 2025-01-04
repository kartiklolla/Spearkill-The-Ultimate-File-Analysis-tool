#include<iomanip>
#include<iostream>
#include<fstream>
using namespace std;
void hexdump(string filename){
    ifstream file(filename, ios::binary);
    if(!file){
        cerr<<"Error opening file for hex dump\n";
        return;
    }
    char buffer;
    cout<<"____________________________________________________\n";
    cout<<"HexDump: \n";
    int i=0;
    while(file.get(buffer)){
        i++;
        cout<<hex<<setw(2)<<setfill('0')<<static_cast<int>(buffer)<<" ";
        if((i)%16==0){
            cout<<"\n";
        }
    }
}
int main(int argc, char *argv[]){
    hexdump(argv[1]);
    return 0;
}