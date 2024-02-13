#include <iostream>
using namespace std;

struct student{
    int matriculation_number, po;
    string first_name, last_name, email, program;
    bool tasks[6];
};


void set_data(student &stud){
    stud.matriculation_number = 3112075;
    stud.first_name = "Mohab";
    stud.last_name = "Ahmed";
    stud.email = "mohab.ahmed@stud.uni-due.de";
    stud.program = "ISE Software Engineering";
    for(int i=0; i<6;i++){
        stud.tasks[i] = false;
    }
}

void output(student &stud){
    cout<< "matr.no.:" <<stud.matriculation_number <<endl
    << "name: " <<stud.first_name <<" " <<stud.last_name <<endl
    <<"email: " <<stud.email <<endl
    <<"course of studies: " <<stud.program <<" (PO " <<stud.po <<")" <<endl
    <<"tasks passed: ";
    cout<< boolalpha;
    for(int i=0; i<6; i++){
        cout<<i+1 <<" " <<stud.tasks[i] <<" ";
    }
    cout<< endl;
}


void input_matriculation_number(student &stud){
    cout<<"please enter matriculation number:";
    cin>> stud.matriculation_number;
}


void set_task_passed(student &stud, int task_num){
    stud.tasks[task_num-1] = true;
}


int main(void)
{
    student mohab;
    set_data(mohab);
    output(mohab);

    input_matriculation_number(mohab);

    mohab.po = 2019;

    set_task_passed(mohab, 1);

    output(mohab);

    return 0;
}
