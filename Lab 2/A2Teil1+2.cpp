/***********************************************************************
Matr.-Nr:                     3112075
Nachname/Surname:             Ahmed
Vorname/Given name:           Mohab
Uni-Email:                    mohab.ahmed@stud.uni-due.de
Studiengang/Course of studis: ISE Computer Engineering (Software Engineering)
***********************************************************************/


#include <iostream>
#include<iomanip>
#include <cstdlib>
#include <string>
using namespace std;


struct Bus{
    int current_passengers, max_passengers;
    float total_distance;
};


struct Stop{
    string stop_name;
    int num_busses_stopped, passengers_on, passengers_off;
    Stop *next;
    float distance_next_stop;
};


//prototypes
void init(Bus &bus);
void output(Bus &bus);
Stop* generate_stop(string s);
Stop* generate_circular_line(int n);
void output(Stop &stop);
void output_whole_line(Stop &stop);
void simulate_get_on_off(Bus *bus, Stop *stop, int on, int off);
float get_length_of_line(Stop *stop);


//definitions
void init(Bus &bus){
    bus.current_passengers = 0;
    bus.max_passengers = 0;
    bus.total_distance = 0;
}


void output(Bus &bus){
    cout<< "bus data: total: " <<bus.total_distance <<" km passengers: actual: " << bus.current_passengers
    <<"  maximum in simulation: " << bus.max_passengers <<endl;
}

Stop* generate_stop(string s){
    Stop *st = new Stop;
    st -> stop_name = s;
    st -> passengers_off = 0; st ->passengers_on = 0; st->num_busses_stopped = 0;
    st -> next = nullptr;
    st->distance_next_stop = 2 + (rand()%(4-2+1));
    return st;
}


Stop* generate_circular_line(int n){
    string num;
    Stop *last_ptr, *previous_ptr, *first_stop_ptr;
    for(int i=1;i<n+1;i++){
        num = to_string(i);
        last_ptr = generate_stop("Bus Stop "+num);
        if(i == 1){
            first_stop_ptr = last_ptr;
            last_ptr->next = first_stop_ptr;
        }
        else{
            previous_ptr ->next = last_ptr;
            last_ptr ->next = first_stop_ptr;
        }
        previous_ptr = last_ptr;

    }
    return first_stop_ptr;
}


void output(Stop &stop){
    cout<<stop.stop_name << ":      to next: " <<stop.distance_next_stop << " km   sums: off: "
    << stop.passengers_off <<"    on: " << stop.passengers_on <<"   stops: " << stop.num_busses_stopped << endl;
}


void output_whole_line(Stop *first_stop){
    Stop *nxt_stop = first_stop;
    do{
        output(*nxt_stop);
        nxt_stop = nxt_stop->next;
    }while(nxt_stop != first_stop);
}


void simulate_get_on_off(Bus *bus, Stop *stop, int on, int off){
    if(bus ->current_passengers < off){
        off = bus ->current_passengers;
    }
    stop ->passengers_on = on;
    stop ->passengers_off = off;
    cout<< "simulate " << stop->stop_name <<":     getting off: " << off
        <<" getting on: " << on << endl;
    bus ->current_passengers = bus ->current_passengers + on - off;
    bus->total_distance += stop->distance_next_stop;
    stop ->num_busses_stopped +=1;
    if(bus->max_passengers < bus->current_passengers) bus->max_passengers = bus->current_passengers;
    cout<< stop->stop_name <<":      to next: " <<stop->distance_next_stop << ":      sums: off: "
    <<off << "    on: " << on << "   stops: " << stop->num_busses_stopped << endl;
}


float get_length_of_line(Stop *stop){
    float result = 0;
    Stop *first = stop, *current = stop;
    do{
        result += current->distance_next_stop;
        current = current->next;

    }while(current != first);
    return result;
}


int main(void)
{

    Bus bus;
    Stop *first_stop_ptr, *current_stop_ptr = new Stop;
    int n_stops, n;

    init(bus);

    cout<< "Eingabe Anzahl Haltestellen / input number of bus stops:";
    cin>> n_stops;
    first_stop_ptr = generate_circular_line(n_stops);
    current_stop_ptr = first_stop_ptr;
    do{
        cout<<"Simulation Ring-Buslinie     / Simulation Bus Circular Line" <<endl
        <<"0 Ende                       / end"<<endl
        <<"1 Daten Bus anzeigen         / show data of bus"<<endl
        <<"2 alle Haltestellen ausgeben / show all bus stops"<<endl
        <<"3 simuliere Stops            / simulate bus stops"<<endl
        <<"4 Laenge der Ring-Buslinie   / length of circular line"<<endl;

        int choice;
        cin>>choice;

        if(choice == 0)break;
        else if(choice ==1) output(bus);
        else if(choice ==2) output_whole_line(first_stop_ptr);
        else if(choice ==3){
            cout<<"Eingabe Anzahl Stops / input number of stops:"<<endl;
            cin>>n;
            for(int i=1;i<n+1;i++){
                simulate_get_on_off(&bus, current_stop_ptr, 1 + (rand() % 9), 1 + (rand() % 9));
                current_stop_ptr = current_stop_ptr->next;
            }

        }else if(choice ==4){
            cout<< "length of circular line: " <<get_length_of_line(current_stop_ptr)<<" km" <<endl;
        }
    }while(true);


    return 0;
}
