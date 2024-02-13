#include <iostream>
using namespace std;

struct student{
    int matriculation_number;
    string first_name, last_name, email, program;
    bool assignments[6];
};


void set_data(student &stud){
    stud.matriculation_number = 3112075;
    stud.first_name = "Mohab";
    stud.last_name = "Ahmed";
    stud.email = "mohab.ahmed@stud.uni-due.de";
    stud.program = "ISE Software Engineering";
    for(int i=0; i<6;i++){
        stud.assignments[i] = false;
    }
}

void output(student &stud){
    cout<< "matr.no.:" <<stud.matriculation_number <<endl
    << "name: " <<stud.first_name <<" " <<stud.last_name <<endl
    <<"email: " <<stud.email <<endl
    <<"course of studies: " <<stud.program <<endl
    <<"tasks passed: ";
    cout<< boolalpha;
    for(int i=0; i<6; i++){
        cout<<i+1 <<" " <<stud.assignments[i] <<" ";
    }
}


int main(void)
{
    student mohab;
    set_data(mohab);
    output(mohab);

    return 0;
}
