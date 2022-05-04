#include <iostream>
#include <cstdlib>
#include "probability.h"

using namespace std;

probability::probability() {
    percentage = 0;
}

probability::probability(int x) {     
    percentage = x;
}

bool probability:: chance(int x) {    //x-percent chance  
    if (((rand() / (float)RAND_MAX) * 100) <= x) {
        return true;
    }
    else {
        return false;
    }
}

bool probability:: chance() {     // percentage- percent chance 
    if (((rand() / (float)RAND_MAX) * 100) <= percentage) {
        return true;
    }
    else {
        return false;
    }
}
