/***********************************************************************
Matr.-Nr:                     3112075
Nachname/Surname:             Ahmed
Vorname/Given name:           Mohab
Uni-Email:                    mohab.ahmed@stud.uni-due.de
Studiengang/Course of studis: ISE Computer Engineering (Software Engineering)
***********************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;


struct Pixel{
    unsigned int red, green, blue;
};


class Image{
private:
    char first_magic_num, second_magic_num;
    unsigned int width, height, max_color_value;
    Pixel **r;
    void alloc_raster(){
        if(r == nullptr && width>0 && height>0){
            r = new Pixel*[width]; // allocate pointers to the rows
            for (unsigned int k = 0; k < width; k++) // for all rows
                r[k] = new Pixel[height]; // allocate pixels in row
        }
    }


public:
    Image():   //definition standard constructor
        first_magic_num('P'),
        second_magic_num('3'),
        width(0),
        height(0),
        max_color_value(255),
        r(nullptr)
    {}


    void write_ppm(string fileName){ //correct width and height
        ofstream outFile;
        outFile.open(fileName);
        cout<<"write_ppm: " <<fileName <<" opened..." <<endl;
        if(outFile.is_open()){
            cout<<"           write header of file..." <<endl;
            outFile <<first_magic_num <<second_magic_num <<endl;
            outFile <<width <<" " <<height<< endl;
            outFile <<max_color_value <<endl;
            outFile <<"# end of header" <<endl;

            cout<<"           write RGB pixel data row by row..." <<endl;
            int h=0;
            for(int w = 0;w<width;w++){
                outFile <<r[w][h].red<<" " <<r[w][h].green<<" "<<r[w][h].blue<<endl;
                h++;
            }
            outFile.close();
            cout<<"           done and " <<fileName <<" closed" <<endl;
        }
    }


    void mirror_vertically(){ //correct width and height
        unsigned int num_of_flips = width/2, temp;
        //Pixel **temp;
        cout<<"           start mirror image vertically..." <<endl;
        for(int h=0;h<height;h++){
            for(int w=0;w<width;w++){
                cout<<r[w][h].red<<" " <<r[w][h].green<<" "<<r[w][h].blue<<endl;
            }
        }
        for(int i=0;i<height;i++){
            for(int j=0;j<num_of_flips;j++){
                swap(r[j][i].red, r[width-j][i].red);
                swap(r[j][i].green, r[width-j][i].green);
                swap(r[j][i].blue, r[width-j][i].blue);
            }
        }
        cout<<"           done" <<endl;
    }


    void read_ppm(string fileName){
        ifstream inFile;
        inFile.open(fileName);
        cout<<"read_ppm:  " <<fileName <<" opened..." <<endl;
        string text;

        cout<<"           read header of file..." <<endl;
        getline(inFile, text); //first line
        first_magic_num = text[0];
        second_magic_num= text[1];

        getline(inFile, text); //second line
        istringstream word(text);
        word>> width >>height;

        getline(inFile, text); //third line
        max_color_value = stoi(text);

        getline(inFile, text); //fourth line / skipped

        cout<<"          allocate "<<width <<"x"<<height<<" pixel array on heap... done" <<endl;
        alloc_raster();

        cout<<"           read RGB pixel data row by row..." <<endl; //only that remaining
        unsigned int j=0;
        for(int i = 0;i<height;i++){
            getline(inFile, text);
            istringstream word2(text);
            word2>> r[i][j].red >>r[i][j].green>>r[i][j].blue;
            j++;
        }
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                cout<<r[j][i].red<<" " <<r[j][i].green<<" "<<r[j][i].blue<<endl;
            }
        }
        inFile.close();
        cout<<"           done and " <<fileName <<" closed" <<endl;
    }

};


int main(void)
{
    Image image1;
    string fileName;
    while(true){
        char choice;
        cout<<"0 Ende                / end" <<endl <<"1 lese .ppm Datei     / read .ppm file" <<endl <<"2 vertikal spiegeln   / mirror vertically" <<endl <<"3 schreibe .ppm Datei / write .ppm file" <<endl;
        cin>> choice;
        if(choice =='0') return 0;
        else if(choice =='1'){
            cout<< "please input file name:";
            cin>> fileName;
            image1.read_ppm(fileName);
        }else if(choice =='2') image1.mirror_vertically();
        else if(choice == '3'){
            cout<< "please input file name:";
            cin>> fileName;
            image1.write_ppm(fileName);
        }
    }





    return 0;
}
