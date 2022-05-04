#include <iostream>
#include <cstdlib>
#include "structs.h"

using namespace std;

void name::printName(){
    cout << a;
}

damage_range::damage_range(){
    low =0;
    high = 10;
}

damage_range::damage_range(int l, int h) {
        low = l;
        high = h;
    }

damage_range::damage_range(damage_range &d){
        low = d.low;
        high = d.high;
    }

    void damage_range:: increase(double i) {   //increases damage range
        low = (int)(((double)low) * i);
        high = (int)(((double)high) * i);
    }

    void damage_range:: decrease(double i) {   //decreases damage range 
        low = (int)(((double)low) * i);
        high = (int)(((double)high) * i);
    }

    void damage_range::print() {  
        cout << "Damage range: " << low << " - " << high << endl;
    }

    coordinates::coordinates(){
        x = 0;
        y=0;
    }