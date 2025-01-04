#include<bits/stdc++.h>
#include<magic.h>
using namespace std;
void file_type(string file_name){
    magic_t magic_pointer;
    magic_pointer = magic_open(MAGIC_MIME_TYPE);//Multi Internet Mail Extensions string. 
    if (magic_pointer == NULL) {
        cout<<"unable to open magic library\n";
        return;
    }
    if (magic_load(magic_pointer, NULL) != 0) {
        cout<<"cannot load magic database - "<<magic_error(magic_pointer)<<"\n";
        magic_close(magic_pointer);
        return;
    }
    const char *mime = magic_file(magic_pointer, file_name.c_str());
    if (mime == NULL) {
        cout<<"cannot determine file type\n";
    } else {
        cout<<file_name<<": "<<mime<<"\n";
    }
    magic_close(magic_pointer);
}
int main(int argc, char *argv[]){
    file_type(argv[1]);
    return 0;
}