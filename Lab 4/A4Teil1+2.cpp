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
            r = new Pixel*[height]; // allocate pointers to the rows
            for (unsigned int k = 0; k < height; k++) // for all rows
                r[k] = new Pixel[width]; // allocate pixels in row
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
        cout<<"           start mirror image vertically..." <<endl;
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

        inFile.close();
        cout<<"           done and " <<fileName <<" closed" <<endl;
    }


    void sepia(){
        cout<<"           start sepia filter..." <<endl;
        for(int h=0;h<height; h++){
            for(int w=0;w<width;w++){
                unsigned int re = r[w][h].red, g = r[w][h].green, b = r[w][h].blue;
                r[w][h].red = 0.393 * re + 0.769 * g + 0.189 * b;
                r[w][h].green = 0.349 * re + 0.686 * g + 0.168 * b;
                r[w][h].blue = 0.272 * re + 0.534 * g + 0.131 * b;
                if(r[w][h].red > 255) r[w][h].red = 255;
                if(r[w][h].green > 255) r[w][h].green = 255;
                if(r[w][h].blue > 255) r[w][h].blue= 255;
            }
        }
        cout<<"           done" <<endl;
    }


    void strip_curtain(const unsigned int strips_width, const unsigned int distance, unsigned int R, unsigned int G, unsigned int B){
        cout<<"           start generating strip curtain of width " <<strips_width <<" and distance " <<distance <<"..." <<endl;
        for(int w=distance; w<width; w+=distance){
            if(w>width) break;
            for(int i = w; i<strips_width+w;i++){
                for(int h=0;h<height;h++){
                    r[i][h].red = R;
                    r[i][h].green = G;
                    r[i][h].blue = B;
                }
            }
            w+=strips_width;
        }

        cout<<"           done" <<endl;
    }
};


int main(void)
{
    Image image1;
    string fileName;
    while(true){
        char choice;
        cout<<"0 Ende                / end" <<endl <<"1 lese .ppm Datei     / read .ppm file" <<endl <<"2 vertikal spiegeln   / mirror vertically" <<endl <<"3 schreibe .ppm Datei / write .ppm file" <<endl
            <<"4 Sepia Filter (Vergilbung) / sepia filter (yellowing)" <<endl <<"5 Streifenvorhang           / strip curtain" <<endl;
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
        }else if(choice == '4') image1.sepia();
        else if(choice =='5'){
            unsigned int wi,d,r,g,b;
            cout<<"please input width of strips: ";
            cin>>wi;
            cout<<"please input distance between strips: ";
            cin>>d;
            cout<<"please input R G B values: ";
            cin>>r>>g>>b;
            image1.strip_curtain(wi,d,r,g,b);
        }
    }





    return 0;
}
