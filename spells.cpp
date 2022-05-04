#include <iostream>
#include <vector>
#include <fstream>
#include "structs.h"
#include "spells.h"

using namespace std;

Spell::Spell():dmg(20,30) {
        price = 0; 
        level_exp = 0;
        magic_power = 0;
    }

    Spell::Spell(int l , int h) :dmg(l, h) {
        price = 0;
        level_exp = 0;
        magic_power = 0;
    }


    Spell::Spell(string a, int p , int l, damage_range d, int mp):dmg(d){
        name_Spell.a = a;
        price = p;
        level_exp = l;
        magic_power = mp;
    }
    
    double Spell:: doubleRand(double fMin, double fMax){ //static function for generating random double from fmin to fmax
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    int Spell::Damage(int dexterity) { // calculates damage taking into consideration dexterity 
        double i = (double)dexterity / (double)100; // dexterity is above 100 so i > 1
        dmg.increase(i);
        return rand() % (dmg.high - dmg.low + 1) + dmg.low; // random from low to high
    }

    int Spell::getMagic()const{
        return magic_power;
    }

    int Spell::getPrice()const{
        return price;
    }

    int Spell::getLevel()const{
        return level_exp;
    }

    void Spell::printName(){
        name_Spell.printName();
    }

    void Spell::print(){
        printName();
        cout << endl;
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
    }    

    void Spell::action(damage_range &dmg, int &defense ,int& dodge, int &mana) {   // what the spell does to the enemy 

    }

    Ice_Spell::Ice_Spell(string a, int p, int l, damage_range d, int mp, double r):Spell(a,p,l,d,mp) {
        reduce_damage = r;
    }

    Ice_Spell::Ice_Spell(){
        reduce_damage = 0;
    }

    Ice_Spell::Ice_Spell(int l , int h, double rdmg):Spell(l,h) {
        reduce_damage = rdmg;
    }

    void Ice_Spell::print(){
        cout << "Ice Spell : ";
        printName();
        cout << endl;
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
        cout << "Enemy Damage reduction multiplier : " << reduce_damage << endl;
    }   

    vector<Ice_Spell*> Ice_Spell::create(int amount){   //same as others 
        vector<Ice_Spell*> w;
        vector<string> s;
        string st;
        ifstream names("spells.txt");
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);
            }
        }else{
            cout << "Cannot open spells" << endl;
            vector<Ice_Spell*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;
            double reduce = doubleRand(0.6 , 0.9);
            damage_range d(rand()%40, rand()%41 + 40);
            int mp = rand()%60 + 10;
            int cost = rand()%(level*10) + level*100;
            w.push_back(new Ice_Spell(s[rand()%s.size()], cost , level, d , mp , reduce));
        }
        names.close();
        return w;
    }

    void Ice_Spell::action(damage_range &dmg, int &defense ,int& dodge, int &mana) {   
        if(magic_power <= mana){    // if you have enought magic power 
            dmg.decrease(reduce_damage);    // decrease dmg range 
        }else{
            cout << "Not enough magic power" << endl;
        }
    }

    Ice_Spell::~Ice_Spell() {

    }

    Fire_Spell::Fire_Spell() {
        reduce_defense = 0.8;
    } 

    Fire_Spell::Fire_Spell(string a, int p , int l , damage_range d , int mp , double r):Spell(a,p,l,d,mp){
        reduce_defense = r;
    }

    vector<Fire_Spell*> Fire_Spell::create(int amount){  // same as others 
        vector<Fire_Spell*> w;
        vector<string> s;
        string st;
        ifstream names("spells.txt");
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);
            }
        }else{
            cout << "Cannot open spells" << endl;
            vector<Fire_Spell*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;
            double reduce = doubleRand(0.6 , 0.9);
            damage_range d(rand()%40+5, rand()%41 + 40);
            int mp = rand()%100 + 10;
            int cost = rand()%(level*10) + level*100;
            w.push_back(new Fire_Spell(s[rand()%s.size()], cost , level, d , mp , reduce));
        }
        names.close();
        return w;
    }

    void Fire_Spell::print(){
        cout << "Fire Spell : ";
        printName();
        cout << endl;
        dmg.print();
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
        cout << "Enemy Defense reduction multiplier : " << reduce_defense << endl;
    }

    void Fire_Spell::action(damage_range &dmg, double &defense ,int& dodge, int &mana) {
        if(magic_power <= mana){
            defense = ((double)defense * reduce_defense);
        }else{
            cout << "Not enough magic power" << endl;
        }
    }

    Fire_Spell::~Fire_Spell() {

    }

    Lightning_Spell::Lightning_Spell() {
        reduce_chance = 0.9;
    }

    Lightning_Spell::Lightning_Spell(double rc) {
        reduce_chance = rc;
    }  

    Lightning_Spell::Lightning_Spell(string a, int p , int l , damage_range d , int mp , double r):Spell(a,p,l,d,mp){
        reduce_chance = r;
    }

    vector<Lightning_Spell*> Lightning_Spell::create(int amount){ // same as others 
        vector<Lightning_Spell*> w;
        vector<string> s;
        string st;
        ifstream names("spells.txt");
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);
            }
        }else{
            cout << "Cannot open spells" << endl;
            vector<Lightning_Spell*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;
            double reduce = doubleRand(0.6 , 0.9);
            damage_range d(rand()%40, rand()%41 + 40);
            int mp = rand()%100 + 10;
            int cost = rand()%(level*10) + level*100;
            w.push_back(new Lightning_Spell(s[rand()%s.size()], cost , level, d , mp , reduce));
        }
        names.close();
        return w;
    }

    void Lightning_Spell::print(){
        cout << "Lightning Spell : ";
        printName();
        cout << endl;
        dmg.print();
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
        cout << "Enemy Dodge reduction multiplier : " << reduce_chance << endl;
    }

    void Lightning_Spell::action(damage_range &dmg, int &defense ,int& dodge, int &mana) {
        if(magic_power <= mana){
            dodge = (int)((double)dodge * reduce_chance);
        }else{
            cout << "Not enought magic power" << endl;
        }
    }

    Lightning_Spell::~Lightning_Spell() {

    }