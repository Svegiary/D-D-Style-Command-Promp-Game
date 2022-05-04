#include <iostream>
#include <vector>
#include <fstream>
#include "structs.h"
#include "items.h"

using namespace std;

    Item::Item(){
        level_exp = 0;
        price = 0;
    }

    Item::Item(string a, int cost , int level){
        name_Item.a = a;
        price = cost ; 
        level_exp = level;
    }   

    double Item::doubleRand(double fMin, double fMax){ // generate random number from fmin to fmax
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    int Item::equip(int &dmg, double &armor , int &strength , int &agility, int &dexterity) {
        return -1;
    }

    int Item::getPrice() const{
        return price;
    }

    int Item::getLevel()const {
        return level_exp;
    }

    void Item::print() {

    }    

    void Item::printName(){
        name_Item.printName();
    }

    Weapon::Weapon(){
        damage = 2;
        hand_use = 1;
    }

    Weapon::Weapon(int dmg, int hu) {
        damage = dmg;
        hand_use = hu;
    }

    Weapon::Weapon(string s , int dmg , int hu , int cost , int min_lvl):Item(s,cost,min_lvl){
        damage = dmg;
        hand_use = hu;
    }

    vector<Weapon*> Weapon::create(int amount){  // static function for creating weapons and returning a vector of pointers pointing to those weapons
        vector<Weapon*> w;  
        vector<string> s;
        string st;
        ifstream names("weapons.txt");  //opens file weapons.txt
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);    // store names in a string vector
            }
        }else{
            cout << "Cannot open weapons" << endl;
            vector<Weapon*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;   // random minimum level from 1-3
            int dmg = rand()%20 + 200;  //random damage from 200-219
            int hu = rand()%2 + 1;  // random hand use from 1-2 
            int cost = rand()%(level*10) + level*100;   //  //random cost, dependant on the minimum level
            w.push_back(new Weapon(s[rand()%s.size()], dmg , hu , cost , level));
        }        

        names.close(); //closes the file        

        return w;   //returns the vector
    }  

    int Weapon::getDamage()const {
        return damage;
    }

    int Weapon::equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity) {    //equips the weapon and changes the extra damage value
       extra_dmg = damage;
       return 0;
    }

    int Weapon::getHandUse()const {
        return hand_use;
    }    

    void Weapon::print(){
        printName();
        cout << "\tDamage :" << damage << "\tHand use: " << hand_use;
        cout << "\tMin level : " << level_exp << "\tPrice : " << price << endl;        
    }    

    Weapon::~Weapon() {

    }

    Armor::Armor() {
        reduce_damage = 0.9;
    }

    Armor::Armor(string s , int cost , int min_level, double reduce):Item(s,cost, min_level){
        reduce_damage = reduce;
    }       

    vector<Armor*> Armor::create(int amount){ // same as weapon
        vector<Armor*> w;
        vector<string> s;
        string st;
        ifstream names("armor.txt");
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);
            }
        }else{
            cout << "Cannot open armor" << endl;
            vector<Armor*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;
            double reduce = doubleRand(0.7 , 0.9); // calls static function to get random double from 0.7 to 0.9
            int cost = rand()%(level*10) + level*100;
            w.push_back(new Armor(s[rand()%s.size()], cost , level, reduce));
        }

        names.close();

        return w;
    }

    double Armor::getRD() const {	
        return reduce_damage;
    }   

    int Armor::equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity) { // changes the value of armor (of the hero down the line)
        armor = reduce_damage;
        return 0;
    }

    void Armor::print(){
        printName();
        cout << "\tDamage Multiplier :" << reduce_damage;
        cout << "\tMin level : " << level_exp << "\tPrice : " << price << endl;        
    }    

    Armor::~Armor() {

    }

    Potion::Potion(){
        upgrade = 1;
    }

    Potion::Potion(string a , double i, int cost, int level):Item(a, cost, level){
        upgrade = i;
    }

    int Potion::equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity) {

        return -1;
    } 

    Potion::~Potion() {

    }

    DexterityPotion::DexterityPotion(){

    }

    DexterityPotion::DexterityPotion(string a , double i, int c, int l):Potion(a,i,c,l){

    }  

    void DexterityPotion::print(){
        cout << "Dexterity Potion : " ;name_Item.printName();
        cout << "\tPrice : " << price << "\tMinimum Level: " << level_exp << endl;
    }

    vector<DexterityPotion*> DexterityPotion::create(int amount){ // same principle as weapon and armor 
        vector<DexterityPotion*> w;
        vector<string> s;
        string st;
        ifstream names("potions.txt");
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);
            }
        }else{
            cout << "Cannot open armor" << endl;
            vector<DexterityPotion*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;
            double upgrade = doubleRand(1.2 , 1.4); //upgrade multiplier
            int cost = rand()%(level*10) + level*100;
            w.push_back(new DexterityPotion(s[rand()%s.size()],upgrade, cost , level));
        }

        names.close();

        return w;
    }

    int DexterityPotion::equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity){ //dexterity potion affects hero's dexterity 
        dexterity = (int)(((double)dexterity) * upgrade);
        return -1;
    }

    AgilityPotion::AgilityPotion(){

    }

    AgilityPotion::AgilityPotion(string a , double i, int c, int l):Potion(a,i,c,l){

    }    

    void AgilityPotion::print(){
        cout << "Agility Potion : " ;name_Item.printName();
        cout << "\tPrice : " << price << "\tMinimum Level: " << level_exp << endl;
    }

    vector<AgilityPotion*> AgilityPotion::create(int amount){   // same as others 
        vector<AgilityPotion*> w;
        vector<string> s;
        string st;
        ifstream names("potions.txt");
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);
            }
        }else{
            cout << "Cannot open potions" << endl;
            vector<AgilityPotion*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;
            double upgrade = doubleRand(1.2 , 1.4);
            int cost = rand()%(level*10) + level*100;
            w.push_back(new AgilityPotion(s[rand()%s.size()],upgrade, cost , level));
        }

        names.close();
        return w;
    }

    int AgilityPotion::equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity){ //agility potions upgrades agility 
        agility = (int)(((double)agility) * upgrade);
        return -1;
    }

    StrengthPotion::StrengthPotion(){

    }

    StrengthPotion::StrengthPotion(string a , double i, int c, int l):Potion(a,i,c,l){

    }


    void StrengthPotion::print(){
        cout << "Strength Potion : " ;name_Item.printName();
        cout << "\tPrice : " << price << "\tMinimum Level: " << level_exp << endl;
    }

    vector<StrengthPotion*> StrengthPotion::create(int amount){ // same as others 
        vector<StrengthPotion*> w;
        vector<string> s;
        string st;
        ifstream names("potions.txt");
        if(names.is_open()){
            while(getline(names,st)){
                s.push_back(st);
            }
        }else{
            cout << "Cannot open armor" << endl;
            vector<StrengthPotion*> empty;
            return empty;
        }

        for(int i = 0; i < amount ; i++){
            int level = rand()%3 + 1;
            double upgrade = doubleRand(1.2 , 1.4);
            int cost = rand()%(level*10) + level*100;
            w.push_back(new StrengthPotion(s[rand()%s.size()],upgrade, cost , level));
        }
        names.close();
        return w;
    }


    int StrengthPotion::equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity){ //strength potion upgardes strength 
        strength = (int)(((double)strength) * upgrade);
        return -1;
    }


