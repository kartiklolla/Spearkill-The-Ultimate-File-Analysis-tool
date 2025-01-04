#include<iostream>
#include<vector>
#include<fstream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//function performing LSB decryption
string extractLSB(string image_file){
    Mat image = imread(image_file,IMREAD_COLOR);
    if(image.empty()){
        cerr<<"Error Loading Image file\n";
        return " ";
    }
    string hidden_data;
    int bit_count=0;
    char current_char=0;

    for(int i=0;i<image.rows;++i){
        for(int j=0;j<image.cols;++j){
            Vec3b pixel = image.at<Vec3b>(i,j);
            for(int k=0;k<3;k++){ //iterates over B,G,R
                current_char = (current_char<<1)|(pixel[k]&1);
                ++bit_count;
                if(bit_count==8){
                    if(current_char=='\0'){
                        return hidden_data;
                    }
                    hidden_data+=current_char;
                    bit_count=0;
                    current_char=0;
                }
            }
        }
    }
    return hidden_data;
}
int main(int argc,char *argv[]){
    if(argc<3){
        cerr<<"Usage:"<<argv[0]<<"<image_file> <outputfile_name>\n";
        return 1;
    }
    string image_file=argv[1];
    string output_file=argv[2];
    string hidden_data=extractLSB(image_file);
    ofstream file(output_file);
    if(!file){
        cerr<<"Error creating output file\n";
        return 1;
    }
    file<<hidden_data;
    cout<<"Data successfully saved to"<<output_file<<endl;
    return 0;
}
