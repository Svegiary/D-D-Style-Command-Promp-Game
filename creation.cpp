#include <iostream>
#include <vector>
#include "structs.h"
#include "items.h"
#include "spells.h"
#include "inventory.h"
#include "living.h"
#include "creation.h"

using namespace std;

    MonsterCreation::MonsterCreation(){
       
    }

    double MonsterCreation::doubleRand(double fMin, double fMax){ //generates random double from fmin to fmax 
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    vector<Monster*> MonsterCreation::getMonsters(vector<Hero*>h){
        for(int i = 0 ; i < h.size(); i++){ //for each hero 
            int random = rand()%3;  //choose randonly what type of monster to create 
            if(random == 0){
                damage_range d(rand()%10 + 80 , rand()%20 + 100);//random damage range from 80 to 119
                double def = doubleRand(0.8 , 0.9);
                int dod = rand()%20 + 100;//random dodge value 
                int hp = rand()%100 + 200;//random hp value 
                m.push_back(new Dragon("Red",h[i]->getLevel(),hp,d,def,dod));   //create dragon with above values and level same as the i-th hero
            }else if(random == 1){
                damage_range d(rand()%10 + 80 , rand()%20 + 90);
                double def = doubleRand(0.85 , 0.9);
                int dod = rand()%20 + 110;
                int hp = rand()%100 + 100;
                m.push_back(new Spirit("Ghost",h[i]->getLevel(),hp,d,def,dod));
            }else if(random == 2){
                damage_range d(rand()%10 + 80 , rand()%20 + 100);
                double def = doubleRand(0.75 , 0.85);
                int dod = rand()%20 + 100;
                int hp = rand()%100 + 300;
                m.push_back(new Exoskeleton("Armored",h[i]->getLevel(),hp,d,def,dod));
            }
        }
        return m;   //return the vector 
    }

    MonsterCreation::~MonsterCreation(){
        for(int i = 0; i < m.size(); i++){
            delete m[i];
        }
    }

    HeroCreation::HeroCreation(){

    }

    vector<Hero*> HeroCreation::getHeros(int amount){ //create amount heros 
        for(int k = 0; k < amount; k++){
            //.........choose what hero to create................
            cout << "\nWhat hero do you want to create?" << endl;
            cout << "1) Warrior\t2) Sorcerer\t3) Paladin" << endl;
            int option;
            cin >> option;
            int level;
            //...................................................

            //...........choose the level of your hero...........
            cout << "What level is your hero going to be: ";
            cin >> level;
            //...................................................

            //.....name your hero..
            cout << "Name: ";
            string a;
            cin >> a;
            //.....................

            if(option ==1){
                int s = rand()%20 + 110;
                int d = rand()%20 +100;
                int ag = rand()%20 + 110;
                int hp = rand()%100 + 700;
                h.push_back(new Warrior(a,level,hp,s,d,ag,k+1));
            }else if(option == 2){
                int s = rand()%20 + 100;
                int d = rand()%20 +110;
                int ag = rand()%20 + 110;
                int hp = rand()%100 + 700;
                h.push_back(new Sorcerer(a,level,hp,s,d,ag,k+1));
            }else if(option == 3){
                int s = rand()%20 + 110;
                int d = rand()%20 +110;
                int ag = rand()%20 + 100;
                int hp = rand()%100 + 700;
                h.push_back(new Paladin(a,level,hp,s,d,ag,k+1));
            }
        }
        return h;
    }

    HeroCreation::~HeroCreation(){
        for(int i = 0; i < h.size(); i++){
            delete h[i];
        }
    } 

