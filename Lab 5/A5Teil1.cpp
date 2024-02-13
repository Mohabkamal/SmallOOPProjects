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
#include <iomanip>

using namespace std;


class Bus{ //done
private:
    bool local_transport;
    float km;


    float get_co2_pkm(){
        if(local_transport) return 0.111;
        else return 0.036;
    }


public:
    Bus(){ //definition standard constructor
        int choice;
        cout<<"bus travel data input:" <<endl <<"(1) local transport" <<endl <<"(2) long distance"
        <<endl <<"your choice: ";
        cin>>choice;
        if(choice == 1) local_transport = true;
        else local_transport = false;

        cout<<"kilometers: ";
        cin>>km;
    }


    Bus(bool local, float kilometers){ // constructor with 2 parameters
        local_transport = local;
        km = kilometers;
    }


    float get_co2(){
        float total_emission;
        total_emission = km * get_co2_pkm();
        return total_emission;
    }


    void print(){
        cout<<"bus travel ";
        if(local_transport) cout<<"local transport: ";
        else cout<<"long distance: ";

        cout<<fixed <<setprecision(1) <<km <<" km ("
        <<fixed <<setprecision(3) <<get_co2_pkm() <<" kg CO2/pkm) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;
    }
};


class Car{ //done
private:
    float l_fuel_km, km;


    float get_co2_km(){
        return (2.3*l_fuel_km)/100;
    }

public:
    Car(){ //standard constructor
        cout<<"passenger car travel data input:" <<endl <<"consumption liter petrol per 100 kilometers: ";
        cin>>l_fuel_km;
        cout<<"kilometers: ";
        cin>>km;
    }


    Car(float l, float kilo){ //constructor with 2 parameters
        l_fuel_km = l;
        km = kilo;
    }


    float get_co2(){
        return km*get_co2_km();
    }


    void print(){
        cout<<"passenger car travel: " <<fixed <<setprecision(1) <<km <<" km ("
        <<fixed <<setprecision(3) <<get_co2_km() <<" kg CO2/km) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;
    }
};


class Cruise{ //done
private:
    float days, sea_days;

    float get_co2_day(bool seaday){
        if(seaday) return 280;
        else return 190;
    }

public:
    Cruise(){ //standard constructor
        cout<<"cruise holiday data input:" <<endl <<"number of days of the whole cruise: ";
        cin>>days;
        cout<<"number of sea days: ";
        cin>>sea_days;
    }


    Cruise(float d, float sea_d){ //constructor with 2 parameters
        days = d;
        sea_days = sea_d;
    }


    float get_co2(){
        float total = sea_days * get_co2_day(true) + (days - sea_days) * get_co2_day(false);
        return total;
    }


    void print(){
        cout<<"cruise holiday (without flights): " <<setprecision(0) <<days <<" days duration with " <<setprecision(0) <<sea_days
        <<" sea days (sea day " <<fixed <<setprecision(3) <<get_co2_day(true) <<" kg CO2/pkm, harbour day "
        <<fixed <<setprecision(3) <<get_co2_day(false) <<" kg CO2/pkm) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;
    }

};


class Flight{ //done
private:
    float km;

    float get_co2_pkm(){
        return 0.27;
    }
public:
    Flight(){ //standard constructor
        cout<<"flight travel data input:" <<endl <<"kilometers: ";
        cin>>km;
    }


    Flight(float kilometers){ //constructor with 1 parameter
        km = kilometers;
    }


    float get_co2(){
        return km*get_co2_pkm();
    }


    void print(){
        cout<<"flight travel: " <<fixed <<setprecision(1) <<km <<" km ("
        <<fixed <<setprecision(3) <<get_co2_pkm() <<" kg CO2/pkm) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;
    }

};


class Train{ //done
private:
    bool local_transport, one_way;
    float km;

    float get_co2_pkm(){
        if(local_transport) return 0.085;
        else return 0.035;
    }

public:
    Train(){ //standard constructor
        int choice;
        cout<<"train travel data input:" <<endl <<"(1) local transport" <<endl <<"(2) long distance"
        <<endl <<"your choice: ";
        cin>>choice;
        if(choice == 1) local_transport = true;
        else local_transport = false;

        cout<<"kilometers: ";
        cin>>km;

        cout<<"(1) one-way" <<endl <<"(2) return" <<endl <<"your choice: ";
        cin>>choice;
        if(choice == 1) one_way = true;
        else one_way = false;
    }


    Train(bool local, float kilometers, bool one_w){ //Constructor with 3 parameters
        local_transport = local;
        km = kilometers;
        one_way = one_w;
    }


    float get_co2(){
        float co2 = km*get_co2_pkm();
        if(!one_way) co2*=2;
        return co2;
    }


    void print(){
        cout<<"train travel ";
        if(local_transport) cout<<"local transport: ";
        else cout<<"long distance: ";

        cout<<fixed <<setprecision(1) <<km <<" km (";
        if(one_way) cout<<"one way, ";
        else cout<<"return, ";
        cout<<fixed <<setprecision(3) <<get_co2_pkm() <<" kg CO2/pkm) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;
    }
};



int main(void)
{

    Bus b1;
    Bus *b2 = new Bus(true, 2200);
    b1.print();
    b2->print();
    cout<<endl <<endl;

    Car c1;
    Car *c2 = new Car(7.5, 5500);
    c1.print();
    c2->print();
    cout<<endl <<endl;

    Cruise h1;
    Cruise *h2 = new Cruise(14, 3);
    h1.print();
    h2->print();
    cout<<endl <<endl;

    Flight f1;
    Flight *f2 = new Flight(2669.9);
    f1.print();
    f2->print();
    cout<<endl <<endl;

    Train t1;
    Train *t2 = new Train(false, 628.8, false);
    t1.print();
    t2->print();
    cout<<endl <<endl;

    float sum=0;
    sum = b1.get_co2() + b2->get_co2() + c1.get_co2() + c2->get_co2() + h1.get_co2() + h2->get_co2()
    + f1.get_co2() + f2->get_co2() + t1.get_co2() + t2->get_co2();

    cout<<"the added total of all CO2 emissions is " <<sum <<" kg = " <<fixed <<setprecision(1) <<sum/1000 <<" tons" <<endl <<endl;
    cout<<"Based purely on the CO2 absorption capacity of nature, each world citizen " <<"should currently afford a maximum of around 2.3 tons per year." <<endl;

    return 0;
}


