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

//Part 1 enum struct Frequency
enum struct Frequency {once, daily, weekly, monthly};
ostream& operator<<(ostream& out, Frequency F){
    switch(F){
        case Frequency::daily: return out<<"daily";
        case Frequency::weekly: return out<<"weekly";
        case Frequency::monthly: return out<<"monthly";
    }
}
istream& operator>>(istream& in, Frequency F){
    cout<<"frequency input:" <<endl <<"(o) once" <<endl <<"(d) daily" <<endl <<"(m) monthly"
    <<endl <<"(w) weekly" <<endl <<"your choice: ";
    char c;
    cin>>c;
    switch(c){
        case 'o': F = Frequency::once;
        case 'd': F = Frequency:: daily;
        case 'm': F = Frequency:: monthly;
        case 'w': F = Frequency:: weekly;
    }
}


//Part 2 CO2Emission
class Co2Emission{
private:
    Co2Emission *next;

public:
    Co2Emission(){ //standard constructor
        next = nullptr;
    }


    virtual ~Co2Emission(){ //virtual destructor
        cout<<"destructor CO2Emission: done" <<endl;
    }


    Co2Emission* get_next(){
        return next;
    }


    void set_next(Co2Emission *ptr){
        next = ptr;
    }


    virtual float get_co2() =0;
    virtual void print() =0;
};


//Part 3 Transport
class Transport : public Co2Emission{
protected:
    float km;
private:
    Frequency frequency;

    virtual float get_co2_pkm() = 0;

public:
    Transport(){ //standard constructor
        cout<<"transport distance kilometers: ";
        cin>>km;
        operator>>(cin, frequency);
    }


    Transport(float KM, Frequency F = Frequency::once){ //constructor with 2 parameters
        km = KM;
        frequency = F;
    }


    virtual ~Transport(){ //virtual destructor
        cout<<" destructor Transport: ";
        operator<<(cout, frequency);
        cout<<" " <<fixed <<setprecision(1) <<km <<" km done" <<endl;
    }


    float get_co2(){
        float result = km* get_co2_pkm();
        switch(frequency){
            case Frequency::once: return result*1;
            case Frequency::daily: return result*365;
            case Frequency::weekly: return result*52;
            case Frequency::monthly: return result*12;
        }
    }


    void print(){
        cout<<"transport ";
        operator<<(cout, frequency);
        cout<<" " <<fixed <<setprecision(1) <<km <<" km ("
        <<fixed <<setprecision(3) <<get_co2_pkm() <<" kg CO2/pkm) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;

    }
};


class Bus : public Transport{
private:
    bool local_transport;


    float get_co2_pkm(){
        if(local_transport) return 0.111;
        else return 0.036;
    }


public:
    Bus() : Transport(){ //definition standard constructor
        int choice;
        cout<<"(1) local transport" <<endl <<"(2) long distance"
        <<endl <<"your choice: ";
        cin>>choice;
        if(choice == 1) local_transport = true;
        else local_transport = false;
    }

    //still
    Bus(bool local, float kilometers): Transport(kilometers){ // constructor with 2 parameters
        local_transport = local;
        //Transport :: km = kilometers;
    }


    void print(){
        cout<<"bus travel ";
        if(local_transport) cout<<"local bus";
        else cout<<"long distance bus";

        Transport::print();
    }


    virtual ~Bus(){ //virtual destructor
        cout<<"  destructor Bus: ";
        Bus::print();
    }
};


class Car : public Transport{ //Task 5
private:
    float l_fuel_km;

    float get_co2_km(){
        return (2.3*l_fuel_km)/100;
    }

public:
    Car() : Transport(){//standard constructor

        cout<<"passenger car consumption liter petrol per 100 kilometers: ";
        cin>>l_fuel_km;
    }



    Car(float l, float kilometers) : Transport(kilometers){ //constructor with 2 parameters
        l_fuel_km = l;
        //km = kilo;
    }


    void print(){
        cout<<"passenger car ";
        Transport::print();
    }


    virtual ~Car(){ //virtual destructor
        cout<<"  destructor Car: ";
        Car::print();
    }
};


class Cruise : public Co2Emission{ //Task 8
private:
    float days, sea_days;

    float get_co2_day(bool seaday){
        if(seaday) return 280;
        else return 190;
    }

public:
    Cruise() : Co2Emission(){ //standard constructor
        cout<<"cruise holiday data input:" <<endl <<"number of days of the whole cruise: ";
        cin>>days;
        cout<<"number of sea days: ";
        cin>>sea_days;
    }


    Cruise(float d, float sea_d) : Co2Emission(){ //constructor with 2 parameters
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


        virtual ~Cruise(){ //virtual destructor
            cout<<"  destructor Cruise: ";
            Cruise::print();
        }

};


class Flight : public Transport{ //Task 6
private:
    float get_co2_pkm(){
        return 0.27;
    }
public:
    Flight() : Transport(){ //standard constructor
    }


    Flight(float kilometers) : Transport(kilometers){ //constructor with 1 parameter
    }


    void print(){
        cout<<"flight ";
        Transport::print();
    }


    virtual ~Flight(){ //virtual destructor
        cout<<"destructor Flight: done" <<endl;
    }

};


class Train : public Transport{ //Task 7
private:
    bool local_transport, one_way;

    float get_co2_pkm(){
        if(local_transport) return 0.085;
        else return 0.035;
    }

public:
    Train() : Transport(){ //standard constructor
        int choice;
        cout<<"(1) local transport train" <<endl <<"(2) long distance train"
        <<endl <<"your choice: ";
        cin>>choice;
        if(choice == 1) local_transport = true;
        else local_transport = false;

        cout<<"(1) one-way" <<endl <<"(2) return" <<endl <<"your choice: ";
        cin>>choice;
        if(choice == 1) one_way = true;
        else one_way = false;
    }


    Train(bool local, float kilometers, bool one_w) : Transport(kilometers){ //Constructor with 3 parameters
        local_transport = local;
        //km = kilometers;
        one_way = one_w;
    }


    float get_co2(){
        float co2 = Transport::get_co2();
        if(!one_way) co2*=2;
        return co2;
    }


    void print(){
        if(one_way) cout<<"one way ";
        else cout<<"return ";

        if(local_transport) cout<<"local train ";
        else cout<<"long distance train ";

        Transport::print();
    }


        virtual ~Train(){ //virtual destructor
            cout<<"  destructor Train: ";
            Train::print();
        }

};


class Solar{
private:
    float kWh;


    float get_co2_kWh(){
        return 0.143;
    }

public:
    Solar(){ //standard constructor
        cout<<"solar power data input:" <<endl <<"kilo Watt hours: ";
        cin>>kWh;
    }


    Solar(float k){ //constructor with 1 parameter
        kWh = k;
    }


    float get_co2(){
        return kWh * get_co2_kWh();
    }


    void print(){
        cout<<"solar power: " <<fixed <<setprecision(1) <<kWh <<" kWh ("
        <<fixed <<setprecision(3) <<get_co2_kWh() <<" kg CO2/kWh) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;
    }
};


class Gas{
private:
    bool bio;
    float kWh;


    float get_co2_kWh(){
        if(bio) return 0.230;
        else return 0.819;
    }
public:
    Gas(){ //standard constructor
        char c;
        cout<<"gas power data input:" <<endl <<"type of gas:" <<endl <<"(b) bio gas" <<endl
        <<"(f) fossil natural gas" <<endl <<"your choice: ";
        cin>>c;
        if(c=='b') bio = true;
        else if(c=='f') bio = false;

        cout<<"kilo Watt hours: ";
        cin>>kWh;
    }

    Gas(float k, bool b=false){ //constructor with 2 parameter
        kWh = k;
        bio = b;
    }


    float get_co2(){
        return kWh * get_co2_kWh();
    }


    void print(){
        if(bio) cout<<"bio gas power ";
        else cout<<"fossil natural gas power ";
        cout<<fixed <<setprecision(1) <<kWh <<" kWh ("
        <<fixed <<setprecision(3) <<get_co2_kWh() <<" kg CO2/kWh) "
        <<fixed <<setprecision(1) <<get_co2() <<" kg CO2" <<endl;
    }
};


class Co2Footprint{
private:
    string name;
    Co2Footprint *emissions;
public:
    Co2Footprint(string s){ //constructor with 1 attribute
        name = s;
        emissions = nullptr;
    }


    ~Co2Footprint(){ //destructor
        cout<<"destructor for CO2Footprint for " <<name <<" started..." <<endl;

        Co2Footprint *temp, *temptemp;
        for(temp = emissions; temp; temp = temptemp){
            temptemp = temp.next;
            delete temp;
        }

        cout<<"destructor CO2Foodprint done" <<endl;

    }


};

int main(void)
{
    Bus b1;

    /*
    Solar s1;
    Solar *s2 = new Solar(87.6);
    s1.print();
    s2->print();
    cout<<endl <<endl;

    Gas g1;
    Gas *g2 = new Gas(87.6);
    g1.print();
    g2->print();
    cout<<endl <<endl;

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
    + f1.get_co2() + f2->get_co2() + t1.get_co2() + t2->get_co2() + s1.get_co2() + s2->get_co2()
    +g1.get_co2() + g2->get_co2();

    cout<<"the added total of all CO2 emissions is " <<sum <<" kg = " <<fixed <<setprecision(1) <<sum/1000 <<" tons" <<endl <<endl;
    cout<<"Based purely on the CO2 absorption capacity of nature, each world citizen " <<"should currently afford a maximum of around 2.3 tons per year." <<endl;
*/
    return 0;
}


