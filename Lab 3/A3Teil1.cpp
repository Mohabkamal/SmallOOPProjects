/***********************************************************************
Matr.-Nr:                     3112075
Nachname/Surname:             Ahmed
Vorname/Given name:           Mohab
Uni-Email:                    mohab.ahmed@stud.uni-due.de
Studiengang/Course of studis: ISE Computer Engineering (Software Engineering)
***********************************************************************/
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;


struct point2D{
    float x_coordinate, y_coordinate;
};


struct circle{
    point2D center;
    float radius;
};


//prototypes
istream& operator>>(istream& in, point2D& pnt);
ostream& operator<<(ostream& out, point2D& pnt);
point2D operator+(point2D& pnt1, point2D& pnt2);
istream& operator>>(istream& in, circle& cir);
ostream& operator<<(ostream& out, circle& cir);
circle operator+(point2D& pnt, circle& cir);
circle operator+(circle& cir, float num);
bool operator==(point2D& pnt1, point2D& pnt2);
bool operator!=(point2D& pnt1, point2D& pnt2);
bool operator==(circle& cir1, circle& cir2);
bool operator!=(circle& cir1, circle& cir2);



istream& operator>>(istream& in, point2D& pnt){
    cout<<"please input x and y coordinate: ";
    in>> pnt.x_coordinate >>pnt.y_coordinate;
}


ostream& operator<<(ostream& out, point2D& pnt){
    //return
     out<<"(" <<pnt.x_coordinate <<"," <<pnt.y_coordinate <<")";
}


point2D operator+(point2D& pnt1, point2D& pnt2){
    point2D sum;
    sum.x_coordinate = pnt1.x_coordinate + pnt2.x_coordinate;
    sum.y_coordinate = pnt1.y_coordinate + pnt2.y_coordinate;
    return sum;

}


istream& operator>>(istream& in, circle& cir){
    cout<<"input center: \n";
    operator>>(cin, cir.center);
    cout<<"please input radius: ";
    cin>> cir.radius;
    if(cir.radius<0){
        cerr << "error in operator>>: negative radius, sign changed \n";
        cir.radius*= -1;
    }

}


ostream& operator<<(ostream& out, circle& cir){
    return out<<"center=" <<cir.center <<", radius=" <<cir.radius <<endl;
}


circle operator+(circle& cir, float num){
    cir.radius += num;
    return cir;
}


circle operator+(point2D& pnt, circle& cir){
    circle new_cir;
    new_cir.center = operator+(pnt, cir.center);
    new_cir.radius = cir.radius;
    return new_cir;

}


bool operator==(point2D& pnt1, point2D& pnt2){
    if(pnt1.x_coordinate == pnt2.x_coordinate && pnt1.y_coordinate == pnt2.y_coordinate) return true;
    else return false;
}


bool operator!=(point2D& pnt1, point2D& pnt2){
    if(pnt1.x_coordinate != pnt2.x_coordinate || pnt1.y_coordinate != pnt2.y_coordinate) return true;
    else return false;
}


bool operator==(circle& cir1, circle& cir2){
    if(operator==(cir1.center, cir2.center) && cir1.radius == cir2.radius) return true;
    else return false;
}


bool operator!=(circle& cir1, circle& cir2){
    if(operator==(cir1.center, cir2.center) == false || cir1.radius != cir2.radius) return true;
    else return false;
}


int main(void)
{
    float num;

    point2D p;
    p.x_coordinate = 1.0;
    p.y_coordinate = 1.0;

    circle c[6];
    c[0].center.x_coordinate = 0.0;
    c[0].center.y_coordinate = 0.0;
    c[0].radius = 1.0;

    operator>>(cin, c[1]);
    operator>>(cin, c[2]);

    for(int i=0;i<3;i++){
        cout<<"c[" <<i <<"]: ";
        operator<<(cout, c[i]);
    }

    cout<<"by adding point (1,1) to c[0] to c[2] assign the results to c[3] to c{5] \n";
    for(int i=0, j=3;i<3;i++, j++){
        c[j] = operator+(p, c[i]);
    }

    for(int i=0;i<6;i++){
        cout<<"c[" <<i <<"]: ";
        operator<<(cout, c[i]);
    }
    cout<< endl;

    cout<<"input value to get added to the radius of c[3] to c{5]: ";
    cin>>num;
    for(int i=3;i<6;i++){
        operator+(c[i], num);
        if(c[i].radius < 0){
            cerr<<"error in operator+: negative radius, radius set to 0.0 instead \n";
            c[i].radius = 0.0;
        }
    }
    for(int i=3;i<6;i++){
        cout<<"c[" <<i <<"]: ";
        operator<<(cout, c[i]);
    }

    cout<<"compare circles: \n";
    if(operator==(c[0], c[1])) cout<<"c[0] and c[1] are equal \n";
    else cout<<"c[0] and c[1] are not equal \n";

    if(operator!=(c[1], c[2])) cout<<"c[1] and c[2] are unequal \n";
    else cout<<"c[1] and c[2] are equal \n";


    return 0;
}
