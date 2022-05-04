/*#include <iostream>
#include <vector>
#include "structs.h"
#include "living.h"
*/

using namespace std;

class MonsterCreation{  
    vector<Monster*>m;
public:
    MonsterCreation();

    static double doubleRand(double fMin, double fMax);

    vector<Monster*> getMonsters(vector<Hero*>h);

    ~MonsterCreation();
};

class HeroCreation{
    vector<Hero*> h;

public:
    
    HeroCreation();

    vector<Hero*> getHeros(int amount);

    ~HeroCreation();
};