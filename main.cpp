#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "constants.h"
#include "probability.h"
#include "structs.h"
#include "items.h"
#include "spells.h"
#include "inventory.h"
#include "market.h"
#include "living.h"
#include "block.h"
#include "creation.h"
#include "grid.h"

using namespace std;


/*
class Item {    //superclass for items
protected:
    name name_Item; //name
    int price;  //cost  
    int level_exp; //minimum level 
public:

    Item() {
        level_exp = 0;
        price = 0;
    }  

    Item(string a, int cost , int level){
        name_Item.a = a;
        price = cost ; 
        level_exp = level;
    }  

    static double doubleRand(double fMin, double fMax){ // generate random number from fmin to fmax
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    virtual int equip(int &dmg, double &armor , int &strength , int &agility, int &dexterity) {
        return -1;
    }

    int getPrice() const{
        return price;
    }

    int getLevel()const {
        return level_exp;
    }

    virtual void print() {

    }    

    void printName(){
        name_Item.printName();
    }

};

class Weapon : public Item {
private:
    int damage; //damage 
    int hand_use;   // hand use

public:

    Weapon(){
        damage = 2;
        hand_use = 1;
    }

    Weapon(int dmg, int hu) {
        damage = dmg;
        hand_use = hu;
    }

    Weapon(string s , int dmg , int hu , int cost , int min_lvl):Item(s,cost,min_lvl){
        damage = dmg;
        hand_use = hu;
    }

    static vector<Weapon*> create(int amount){  // static function for creating weapons and returning a vector of pointers pointing to those weapons
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

    int getDamage()const {
        return damage;
    }

    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity) {    //equips the weapon and changes the extra damage value
       extra_dmg = damage;
       return 0;
    }

    int getHandUse()const {
        return hand_use;
    }    

    void print(){
        printName();
        cout << "\tDamage :" << damage << "\tHand use: " << hand_use;
        cout << "\tMin level : " << level_exp << "\tPrice : " << price << endl;        
    }    

    ~Weapon() {

    }
};

class Armor : public Item {
private:
    double reduce_damage;	 // reduce damage taken (to the Hero) 

public:

    Armor() {
        reduce_damage = 0.9;
    }

    Armor(string s , int cost , int min_level, double reduce):Item(s,cost, min_level){
        reduce_damage = reduce;
    }       

    static vector<Armor*> create(int amount){ // same as weapon
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

    double getRD() const {	
        return reduce_damage;
    }   

    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity) { // changes the value of armor (of the hero down the line)
        armor = reduce_damage;
        return 0;
    }

    void print(){
        printName();
        cout << "\tDamage Multiplier :" << reduce_damage;
        cout << "\tMin level : " << level_exp << "\tPrice : " << price << endl;        
    }    

    ~Armor() {

    }
};

class Potion : public Item {
protected:
     double upgrade;
public:  

    Potion(){
        upgrade = 1;
    }

    Potion(string a , double i, int cost, int level):Item(a, cost, level){
        upgrade = i;
    }

    virtual int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity) {

        return -1;
    } 

    ~Potion() {

    }

};

class DexterityPotion: public Potion{
public:

    DexterityPotion(){

    }

    DexterityPotion(string a , double i, int c, int l):Potion(a,i,c,l){

    }

   

    void print(){
        cout << "Dexterity Potion : " ;name_Item.printName();
        cout << "\tPrice : " << price << "\tMinimum Level: " << level_exp << endl;
    }

    static vector<DexterityPotion*> create(int amount){ // same principle as weapon and armor 
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

    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity){ //dexterity potion affects hero's dexterity 
        dexterity = (int)(((double)dexterity) * upgrade);
        return -1;
    }
};

class AgilityPotion: public Potion{
public:

    AgilityPotion(){

    }

    AgilityPotion(string a , double i, int c, int l):Potion(a,i,c,l){

    }    

    void print(){
        cout << "Agility Potion : " ;name_Item.printName();
        cout << "\tPrice : " << price << "\tMinimum Level: " << level_exp << endl;
    }

    static vector<AgilityPotion*> create(int amount){   // same as others 
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

    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity){ //agility potions upgrades agility 
        agility = (int)(((double)agility) * upgrade);
        return -1;
    }
};

class StrengthPotion : public Potion{
public:

    StrengthPotion(){

    }

    StrengthPotion(string a , double i, int c, int l):Potion(a,i,c,l){

    }


    void print(){
        cout << "Strength Potion : " ;name_Item.printName();
        cout << "\tPrice : " << price << "\tMinimum Level: " << level_exp << endl;
    }

    static vector<StrengthPotion*> create(int amount){ // same as others 
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


    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity){ //strength potion upgardes strength 
        strength = (int)(((double)strength) * upgrade);
        return -1;
    }
};
*/

/*
class Spell {   //spell is not an item
protected:
    name name_Spell;
    int price;  
    int level_exp;  //minimum level
    damage_range dmg;   
    int magic_power;    //magic power cost 
public:
    Spell():dmg(20,30) {
        price = 0; 
        level_exp = 0;
        magic_power = 0;
    }

    Spell(int l , int h) :dmg(l, h) {
        price = 0;
        level_exp = 0;
        magic_power = 0;
    }


    Spell(string a, int p , int l, damage_range d, int mp):dmg(d){
        name_Spell.a = a;
        price = p;
        level_exp = l;
        magic_power = mp;
    }
    
    static double doubleRand(double fMin, double fMax){ //static function for generating random double from fmin to fmax
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    int Damage(int dexterity) { // calculates damage taking into consideration dexterity 
        double i = (double)dexterity / (double)100; // dexterity is above 100 so i > 1
        dmg.increase(i);
        return rand() % (dmg.high - dmg.low + 1) + dmg.low; // random from low to high
    }

    int getMagic()const{
        return magic_power;
    }

    int getPrice()const{
        return price;
    }

    int getLevel()const{
        return level_exp;
    }

    void printName(){
        name_Spell.printName();
    }

    virtual void print(){
        printName();
        cout << endl;
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
    }    

    virtual void action(damage_range &dmg, int &defense ,int& dodge, int &mana) {   // what the spell does to the enemy 

    }    
};

class Ice_Spell : public Spell {
private:
    double reduce_damage;		

public:

    Ice_Spell(string a, int p, int l, damage_range d, int mp, double r):Spell(a,p,l,d,mp) {
        reduce_damage = r;
    }

    Ice_Spell(){
        reduce_damage = 0;
    }

    Ice_Spell(int l , int h, double rdmg):Spell(l,h) {
        reduce_damage = rdmg;
    }

    void print(){
        cout << "Ice Spell : ";
        printName();
        cout << endl;
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
        cout << "Enemy Damage reduction multiplier : " << reduce_damage << endl;
    }   

    static vector<Ice_Spell*> create(int amount){   //same as others 
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

    void action(damage_range &dmg, int &defense ,int& dodge, int &mana) {   
        if(magic_power <= mana){    // if you have enought magic power 
            dmg.decrease(reduce_damage);    // decrease dmg range 
        }else{
            cout << "Not enough magic power" << endl;
        }
    }

    ~Ice_Spell() {

    }


};

class Fire_Spell : public Spell {
private:
    double reduce_defense; 	// reduce defemse 
public:

    Fire_Spell() {
        reduce_defense = 0.8;
    } 

    Fire_Spell(string a, int p , int l , damage_range d , int mp , double r):Spell(a,p,l,d,mp){
        reduce_defense = r;
    }

    static vector<Fire_Spell*> create(int amount){  // same as others 
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

    void print(){
        cout << "Fire Spell : ";
        printName();
        cout << endl;
        dmg.print();
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
        cout << "Enemy Defense reduction multiplier : " << reduce_defense << endl;
    }

    void action(damage_range &dmg, double &defense ,int& dodge, int &mana) {
        if(magic_power <= mana){
            defense = ((double)defense * reduce_defense);
        }else{
            cout << "Not enough magic power" << endl;
        }
    }

    ~Fire_Spell() {

    }
};

class Lightning_Spell : public Spell {
private:
    double reduce_chance;   // reduce chance of dodging the attack 
public:
    Lightning_Spell() {
        reduce_chance = 0.9;
    }

    Lightning_Spell(double rc) {
        reduce_chance = rc;
    }  

    Lightning_Spell(string a, int p , int l , damage_range d , int mp , double r):Spell(a,p,l,d,mp){
        reduce_chance = r;
    }

    static vector<Lightning_Spell*> create(int amount){ // same as others 
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

    void print(){
        cout << "Lightning Spell : ";
        printName();
        cout << endl;
        dmg.print();
        cout << "Level required : " << level_exp;
        cout << "\tPower cost: " << magic_power << endl;
        cout << "Cost : " << price << endl;
        cout << "Enemy Dodge reduction multiplier : " << reduce_chance << endl;
    }

    void action(damage_range &dmg, int &defense ,int& dodge, int &mana) {
        if(magic_power <= mana){
            dodge = (int)((double)dodge * reduce_chance);
        }else{
            cout << "Not enought magic power" << endl;
        }
    }

    ~Lightning_Spell() {

    }
};
*/

/*
class Inventory {
    vector<Item*> item;
    vector<Spell*>spell;
public:
    Inventory() {

    }

    void add_to_inventory(Item *t) {
        item.push_back(t);
    }

    void add_to_inventory(Spell *s){
        spell.push_back(s);
    }

    Inventory* createInventory(){   //creates inventory 
    //used for calling the static function 
        Weapon w;
        Armor a;
        DexterityPotion dp;
        AgilityPotion ap;
        StrengthPotion sp;
        Ice_Spell is;
        Fire_Spell fs;
        Lightning_Spell ls;
    //................creating the items and spells.......
        vector<Weapon*> weapons = w.create(5);
        vector<Armor*> armor = a.create(5);
        vector<DexterityPotion*> dexterity = dp.create(2);
        vector<AgilityPotion*> agility = ap.create(2);
        vector<StrengthPotion*> strength = sp.create(2);
        vector<Ice_Spell*> ice = is.create(3);
        vector<Fire_Spell*> fire = fs.create(3);
        vector<Lightning_Spell*> lightning = ls.create(3);
    //....................................................

    //.................adding them to the inventory........
        for(int i=0 ; i < weapons.size(); i++){
            add_to_inventory(weapons[i]);
        }

        for(int i=0 ; i < armor.size(); i++){
            add_to_inventory(armor[i]);
        }

        for(int i=0 ; i < dexterity.size(); i++){
            add_to_inventory(dexterity[i]);
        }

        for(int i=0 ; i < agility.size(); i++){
            add_to_inventory(agility[i]);
        }
        
        for(int i=0 ; i < strength.size(); i++){
            add_to_inventory(strength[i]);
        }

        for(int i=0 ; i < ice.size(); i++){
            add_to_inventory(ice[i]);
        }

        for(int i=0 ; i < fire.size(); i++){
            add_to_inventory(fire[i]);
        }

        for(int i=0 ; i < lightning.size(); i++){
            add_to_inventory(lightning[i]);
        }
    //.......................................................
        return this; //returns pointer to inventory 
    }

    int equipItem(int k, int &dmg, double &ar, int &strength , int &agility , int &dexterity) { // equips the k-th item
        if (item[k - 1]->equip(dmg,ar,strength , agility , dexterity) != -1) {      //if the item is not a spell 
            return 0;   // equip and dont erase it 
        }
        else {  //if it is a spell 
            Item *it = item[k-1];   
            item.erase(item.begin()+k-1);   //erase the item 
            delete it;  //delete the item
            return -1;
        }
    }

    Spell* equipSpell(int k){   // returns a pointer to the k-th spell 
        if(k <= spell.size()){
            return spell[k-1];
        }else{
            cout << "No such spell" << endl;
            return nullptr;
        }
    }

    Item* select(int k) {   //returns pointer to the k-th item 
        return item[k - 1];
    }

    Item* remove(int k) {   // removes the k-th item 
        Item* it = item[k - 1];
        item.erase(item.begin() + k - 1);        
        return it;
    }

    Spell* select_spell(int k){ //returns pointer to the k-th spell 
        return spell[k-1];
    }

    Spell* remove_spell(int k){ //removes the k-th spell and returns a pointer to it 
        Spell* it = spell[k - 1];
        spell.erase(spell.begin() + k - 1);        
        return it;
    }

    void checkItems() { //prints items 
        cout << "Items are: " << endl;
        for (int i = 0; i < item.size(); i++) {
            cout << i + 1 << ")";
            item[i]->print();
            cout << endl;
        }
    }

    void checkSpells(){ //prints spells 
        cout << "Spells are : " << endl;
        for(int i = 0; i < spell.size(); i++){
            cout << i+1<< ")";
            spell[i]->print();
            cout << endl;
        }
    }

    void checkInventory(){  //prints inventory 
        checkItems();
        checkSpells();
    }

    int menu(int &dmg, double &ar, int &strength , int &agility , int &dexterity){  //inventory menu 
        checkInventory();   //prints inventory 
        int a = 0;
        cout << "Possible actions : 1) Equip Item\n2) Exit" <<endl;
        while(a < 1 && a > 3){
            cout << "Invalid Number" << endl;
            cin >> a;
        }
        if(a == 1){
            cout << "Which Item to equip?" << endl;
            cin >> a;
            equipItem(a,dmg, ar , strength , agility , dexterity);  // equips a-th item and changes stats accordingly 
        }else if( a == 2){
            cout << "Exiting Inventory" << endl;
            return -1;  //-1 if exit 
        }

        return 0;   
    }

    int getItemNumber()const{
        return item.size();
    }

    int getSpellNumber()const{
        return spell.size();
    }

    ~Inventory(){
        for(int i =0; i < item.size(); i++){
            delete item[i];
        }
        for(int i = 0; i < spell.size(); i++){
            delete spell[i];
        }
    }
};
*/
/*
class Market {  //markeplace 
private:
    Inventory *inventory;
public:
    Market() {
        inventory = new Inventory;
    }

    void createMarket(vector<Item*> item, vector<Spell *> spells) { // creates market from two vectors 
        for (int i = 0; i < item.size(); i++) {
            inventory->add_to_inventory(item[i]);
        }
        for(int i = 0; i < spells.size(); i++){
            inventory->add_to_inventory(spells[i]);
        }
    }

    void createMarket(){    //creates inventory using the creation tool from the inventory 
        inventory->createInventory();
    }

    void printMarket() {
        inventory->checkItems();
        inventory->checkSpells();
    }

    int getItemNumber()const{
        return inventory->getItemNumber();
    }

    int getSpellNumber()const{
        return inventory->getSpellNumber();
    }

    Item* buy_from_market(int k) {  // returns a pointer to the k-th item  
        return inventory->select(k);
    }   

    Item* remove(int k){    //removes item from vector and returns a pointer to it 
        return inventory->remove(k);
    }

    Spell* buy_spell_from_market(int k){    //returns a pointer to the k-th spell
        return inventory->equipSpell(k);
    }

    Spell *remove_spell(int k){ //removes spell from vector and returns a pointer to it 
        return inventory->remove_spell(k);
    }

    ~Market(){
        delete inventory;
    }
};
*/
/*
class Living {  //Living base class
protected:        
    name nam;
    int level;
    int healthPower;
    bool dead;
    int max_health;
public:
    Living() {
        level = 1;
        nam.a = "Default Living";
        healthPower = 200;
        dead = false;
        max_health = healthPower;
    }  

    Living(string a) {
        level = 1;
        nam.a = a;
        healthPower = 200;
        dead = false;
        max_health = 200;
    }  

    Living(string a, int lvl , int hp){
        level = 0;
        nam.a = a;
        max_health = hp;
        healthPower = hp;
        dead = false;
    } 

    void nameHero(string a) {
        nam.a = a;
    }

    int getLevel()const {
        return level;
    }

    int getHP()const {
        return healthPower;
    }

    void setlevel(int l) {
        level = l;
    }

    void setHP(int hp){
        healthPower = hp;
    } 

    //virtual functions explained later....................

    virtual int Damage() {
        return -1;
    }

    virtual bool dodged() {
        return -1;
    }

    virtual int is_hurt_by(Living* l) {
        this->healthPower -= l->Damage();
        return -1;
    }

    virtual int getHeroID()const {
        return -2;
    }

    virtual int attack(Living* l) {
        return -2;
    }

    virtual void printMonster() {

    }

    virtual int is_hurt_by_spell(Living *l, int k){
        return -100;
    }

    virtual int is_hurt_by_weapon(Living *l){
        return -100;
    }

    virtual void equipItem(int k){

    }

    virtual Spell* equipSpell(){
        return nullptr;
    }

    virtual void printHero() {

    }

    virtual int spellDamage(int k, Living *l){
        return -100;
    }

    virtual void spellAction(){

    }

    virtual int getDodge()const{
        return -2;
    }

    virtual int getDefense()const{
        return -2;
    }

    virtual damage_range getDmgRange(){
        damage_range dm(0,0);
        return dm;
    }

    virtual void setDmgRange(damage_range dm){

    }

    virtual void setDefense(int d){

    }

    virtual void setDodge(int d){

    }

    virtual void checkItems(){

    }

    virtual void checkSpells(){

    }

    virtual void replenish(){

    }

    //...............................................................................

    bool is_dead(){ //checks if a living is dead 
        return dead;
    }

    virtual void die(){ //kills a living 
        dead = true;
    }

    void printName(){   //prints just the name 
        nam.printName();        
    }

    ~Living() {
        
    }
};

class Monster : public Living { // monster 
protected:
    damage_range dmg;
    double defense;
    int dodge;
public:
    Monster() :Living(), dmg(80, 100) {
        defense = 0.9;
        dodge = 100;
    }

    Monster(string a) :Living(a), dmg(80, 100) {
        defense = 0.9;
        dodge = 100;
    }

    Monster(string a, int lvl, int hp, damage_range d, double def , int dod):dmg(d),Living(a,lvl,hp){
        level = 0;
        defense = def;
        dodge = dod;               
    }

    int Damage() {  //calculates (random) number withing the damage range 
        return rand() % (dmg.high - dmg.low + 1) + dmg.low;
    }

    int getDefense() const {
        return defense;
    }

    int getDodge() const{
        return dodge;
    }

    damage_range getDmgRange(){
        return dmg;
    }

    void setDmgRange(damage_range dm){
        dmg = dm;
    }

    void setDefense(int d){
        defense = d;
    }

    void setDodge(int d){
        dodge = d;
    }
    
    bool dodged() { //calculates if the attack is dodged 
        int p = (int)(dodge / 10);  // dodge is <1000 so p <100 and >0
        probability per(p);
        return per.chance();
    }

    int attack(Living* l) { //monster attacks 
        if (l->dodged()) {  //if the attack was dodged 
            cout << "Attack dodged" << endl;
            return -1;
        }
        else {
            l->is_hurt_by(this);    //l is hurt by this monster 
            cout << "Hero wounded" << endl;
            if (l->getHP() <= 0) {  //if hp < 0
                cout << "Hero defeated" << endl;
                return 1;
            }
            else {
                return 0;
            }
        }
    }

    void replenish(){
        healthPower += 30;
    }

    virtual void printMonster() {

    }

    int is_hurt_by_weapon(Living* h) {  //monster is hurt by weapon 
        int hp_reduction = (int) ( (double)h->Damage() )* (defense); // defense is double <1 and > 0
        healthPower -= hp_reduction;
        return healthPower;
    }

    int is_hurt_by_spell(Living *h, int k){ //monster is hurt by k-th spell 
        int hp_reduction = (int) ( (double)h->spellDamage(k,this) )* (defense); // same as before 
        healthPower -= hp_reduction;
        return healthPower;
    }
};

class Hero : public Living {
protected:
    int magicPower;
    int strength;
    int dexterity;
    int agility;
    int money;
    int xp;
    int weapon_damage;
    Inventory *inventory; 
    coordinates position;
    double armor_multiplier;
    int hero_id;
    int xp_awarded;
    int money_awarded;
    int level_up_xp ;
    int monsters_defeated;
    int max_magic;

public :

    Hero():Living() {
        magicPower = 100;
        strength = 100;
        dexterity = 100;
        agility = 100;
        money = 0;
        xp = 0;      
        weapon_damage = 2; 
        armor_multiplier = 1.0;
        hero_id = 0;
        level_up_xp = level*100;
        monsters_defeated=0;
        money_awarded = 0;
        xp_awarded = 0;
        inventory = new Inventory;
    }

    Hero(string a,int l,int hp,int s,int d, int ag, int id ):Living(a,l,hp){
        magicPower = 100;
        strength = s;
        dexterity = d;
        agility = ag;
        money = 1000;
        xp = 1;
        weapon_damage = 2;
        armor_multiplier = 1.0;
        hero_id = id;
        level_up_xp = (level+1)*100;
        monsters_defeated = 0;
        money_awarded = 0;
        xp_awarded = 0;
        inventory = new Inventory;
    }    

    int Damage() {  //adds weapon damage to hero strength 
        return weapon_damage + strength;
    }   

    Spell* equipSpell(int k){   //equip the k-th spell from the heros inventory and returns a pointer to it       
       return inventory->equipSpell(k);
    }

    int spellDamage(int k, Monster *m){ //applies spell effects on monster and then it calculates the health to be deducted 
        Spell *s = equipSpell(k);
        magicPower -= s->getMagic();    // deducts magic power cost
        damage_range dm; dm.low = m->getDmgRange().low;
        dm.high = m->getDmgRange().high;
        int defense = m->getDefense();
        int dodge = m->getDodge();
        s->action(dm, defense, dodge,magicPower);   //applies spell effects 

        m->setDmgRange(dm);
        m->setDefense(defense);
        m->setDodge(dodge);
        return s->Damage(dexterity);    //returns damage calculated with dexterity in mind 
    }

    coordinates getCoordinates()const {
        return position;    
    }

    int getHeroID()const {   
        return hero_id;
    }

    int buy(Item *t) {  //buys item
        if (money >= t->getPrice() && level >= t->getLevel()) {    //if they have enough money and level 
            inventory->add_to_inventory(t); //add to hero's inventory 
            money -= t->getPrice(); // deduct cost 
            return 0;
        }
        else if(money < t->getPrice()){ // if the hero does not have enough money 
            cout << "Not enough money\n" << endl;
            return -1;
        }else{
            cout << "Not high enough level" << endl;
            return -1;
        }
    }

    int buy_spell(Spell *s){    //buys spell 
        if (money >= s->getPrice() && level >= s->getLevel()) { //if they have enough money and are high enough level
            inventory->add_to_inventory(s); // // add spell to inventory 
            money -= s->getPrice(); //deduct cost
            return 0;
        }
        else if(money < s->getPrice()){
            cout << "Not enough money\n" << endl;
            return -1;
        }else{
            cout << "Not high enough level" << endl;
            return -1;
        }
    }

    int getItemNumber()const{
        return inventory->getItemNumber();
    }

    int getSpellNumber()const{
        return inventory->getSpellNumber();
    }

    Item * sell(int k) {    //sell item
        money = money + (inventory->select(k)->getPrice()/2);   //gets paid 
        cout << "Item sold for " << inventory->select(k)->getPrice() / 2 << endl;   
        Item *t = inventory->remove(k); //remove 
        return t;   //return pointer to item 
    }

    Spell* sell_spell(int k){   //sell spell , same as item 
        money = money + (inventory->select_spell(k)->getPrice()/2);
        cout << "Item sold for " << inventory->select(k)->getPrice() / 2 << endl;
        Spell* s = inventory->remove_spell(k);
        return s;
    }

    bool dodged() { 
        int p = (int)(agility / 10);
        probability per(p);
        return per.chance();
    }

    //..................movement..........................

    bool move_up(){ //moves hero up
        if (position.y -1 >= 0) {   //if he can move up 
            position.y -= 1;    // reduce y value 
            return true;    // he did move up 
        }
        else {
            cout << "End of map" << endl;
            return false;   // he did not move up
        }        
    }

    bool move_right(){
        if (position.x + 1 < length) {
            position.x += 1;
            return true;
        }
        else {
            cout << "End of map" << endl;
            return false;
        }        
    }

    bool move_down() {
        if (position.y + 1 < height ) {
            position.y += 1;
            return true;
        }
        else {
            cout << "End of map" << endl;
            return false;
        }
    }

    bool move_left() {
        if ( position.x - 1 >= 0) {
            position.x -= 1;
            return true;
        }
        else {
            cout << "End of map" << endl;
            return false;
        }
    }
    //.............................................

    void equipItem(int k) { // equips k-th item and applies effects 
        inventory->equipItem(k, weapon_damage, armor_multiplier, strength , agility , dexterity);
    }

    void checkInventory() { //prints inventory 
        inventory->checkInventory();
    }

    void checkItems(){  // checks only items 
        inventory->checkItems();
    }

    void checkSpells(){ //checks only spells 
        inventory->checkSpells();
    }

    int menu(){ 
        return inventory->menu(weapon_damage, armor_multiplier, strength , agility , dexterity);
    }

    virtual void printHero() {

    }

    int castSpell(Living *l, int k){    //casts spell 
        if (l->dodged()) {
            cout << "Spell dodged" << endl;
            return -1;
        }
        else {
            l->is_hurt_by_spell(this, k);
            cout << "Enemy wounded" << endl;
            if (l->getHP() <= 0) {
                cout << "Enemy defeated" << endl;
                return 1;
            }
            else {
                return 0;
            }
        }
    }   

    int attack(Living *l) {
        if (l->dodged()) {
            cout << "Attack dodged" << endl;
            return -1;
        }
        else {
            l->is_hurt_by_weapon(this);
            cout << "Enemy wounded" << endl;
            if (l->getHP() <= 0) {
                cout << "Enemy defeated" << endl;
                return 1;
            }
            else {
                return 0;
            }
        }
    }

    int is_hurt_by(Living *l) {
        int hp_reduction = (int)((double)l->Damage() * armor_multiplier);
        healthPower -= hp_reduction;
        return healthPower;
    }

    virtual void levelUp(){

    }

    void replenish(){   //replenishes health and magic power 
        magicPower += 20;
        healthPower += 30;
    }

    void die(){ //if they die 
        money = money/2;    //reduce money 
        dead = true;    //kill them 
    }
    
    void revive(){
        dead = false;
    }

    void awards(){  //awards for killing monsters 
        monsters_defeated++;    //increase number of monsters defeated 
        money_awarded = (100*((double)level*1.5))*monsters_defeated;
        xp_awarded = (100*((double)level*1.2))*monsters_defeated;
        xp += xp_awarded;
        money += money_awarded;
        if(xp >= level_up_xp){
            cout << "Level up!!" << endl;
            levelUp();
        }
    }    

    ~Hero(){
        delete inventory;
    }
};

class Warrior : public Hero {
public:
    

    Warrior(string a,int l,int hp,int s,int d, int ag , int id):Hero(a,l,hp,s,d,ag,id){
        //.............make them better at...............
        strength = (int)(((double)strength) * better_at); 
        agility = (int)(((double)agility) * better_at);
        //...............................................   
        for(int i = 0; i < l; i++){ //get warrior up to level 
            levelUp();
        }     
    }

    void printHero() {
        cout << "Warrior ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;
        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        cout << "Strength : " << strength << endl;
        cout << "Magic Power : " << magicPower << endl;
        cout << "Dexterity : " << dexterity << endl;
        cout << "Agility : " << agility << endl;
        cout << "Money : " << money << endl;
        cout << "XP : " << xp << endl;
    }
   
    void levelUp() {    // level up
        max_health = (int)(((double)max_health) * normal_at);
        max_magic = (int)(((double)magicPower) * normal_at);
        healthPower = max_health;
        magicPower = max_magic;
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * normal_at);
        agility = (int)(((double)agility) * better_at);
        money += level_up_money;
        level++;
        if(xp < level_up_xp * level){
            xp = level_up_xp * level;
        }
    }
};

class Sorcerer :public Hero {
public:     

    Sorcerer(string a,int l,int hp,int s,int d, int ag, int id ):Hero(a,l,hp,s,d,ag,id){
        //................make them better at..............
        dexterity = (int)(((double)dexterity) * better_at);
        agility = (int)(((double)agility) * better_at);
        //.................................................
        for(int i = 0; i < l; i++){
            levelUp();
        }        
    }

    void printHero() {
        cout << "Sorcerer ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;
        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        cout << "Strength : " << strength << endl;
        cout << "Magic Power : " << magicPower << endl;
        cout << "Dexterity : " << dexterity << endl;
        cout << "Agility : " << agility << endl;
        cout << "Money : " << money << endl;
        cout << "XP : " << xp << endl;
    }

    void levelUp() {
        magicPower = (int)(((double)magicPower) * normal_at);
        strength = (int)(((double)strength) * normal_at);
        dexterity = (int)(((double)dexterity) * better_at);
        agility = (int)(((double)agility) * better_at);
        money += level_up_money;
        level++;
        if(xp < level_up_xp * level){
            xp = level_up_xp * level;
        }
    }
};

class Paladin :public Hero {
public:
    Paladin():Hero() {
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * better_at);
        money = 0;
        xp = 0;
    }   

    Paladin(string a,int l,int hp,int s,int d, int ag , int id):Hero(a,l,hp,s,d,ag,id){
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * better_at);   
        for(int i = 0; i < l; i++){
            levelUp();
        }     
    }

    void printHero() {
        cout << "Paladin ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;
        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        cout << "Strength : " << strength << endl;
        cout << "Magic Power : " << magicPower << endl;
        cout << "Dexterity : " << dexterity << endl;
        cout << "Agility : " << agility << endl;
        cout << "Money : " << money << endl;
        cout << "XP : " << xp << endl;
    }

    void levelUp() {
        max_health = (int)(((double)max_health) * normal_at);
        max_magic = (int)(((double)magicPower) * normal_at);
        healthPower = max_health;
        magicPower = max_magic;
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * better_at);
        agility = (int)(((double)agility) * normal_at);
        money += level_up_money;
        level++;
        if(xp < level_up_xp * level){
            xp = level_up_xp * level;
        }
        
    }
};

class Dragon :public Monster {
public:
    Dragon() {
        dmg.increase(better_at);
    }

    Dragon(string a) :Monster(a) {
        dmg.increase(better_at);    
    }

    Dragon(string a, int lvl,int hp , damage_range d, double def , int dod) :Monster(a,lvl,hp,d,def,dod) {
        dmg.increase(better_at);  //increase damage range    
        for(int i = 0; i < lvl; i++){   // up to desired level 
            levelUp();
        }
    }

    void printMonster() {
        cout << "Dragon "; 
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;

        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        dmg.print();
        cout << "Defense : " << defense << endl;
        cout << "Dodge : " << dodge << endl;
    }  

    void levelUp() {        
        max_health = (int)(((double)max_health) * normal_at);
        healthPower = max_health;
        dmg.increase(better_at);
        defense = ((defense) / 1.05);
        dodge = (int)(((double)dodge) * normal_at);
        level++;
    }
};

class Exoskeleton : public Monster {
public:
    Exoskeleton() :Monster() {
        defense =((defense) / 1.15);
    }    

    Exoskeleton(string a, int lvl ,int hp, damage_range d, double def , int dod) :Monster(a,lvl,hp,d,def,dod) {
        defense = ((defense) / 1.15);   //decrease defense multiplier so decrease incoming damage 
        for(int i = 0; i < lvl; i++){
            levelUp();
        }
    }

    void printMonster() {
        cout << "Exoskeleton ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;

        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        dmg.print();
        cout << "Defense : " << defense << endl;
        cout << "Dodge : " << dodge << endl;
    }

    void levelUp() {
        max_health = (int)(((double)max_health) * normal_at);
        healthPower = max_health;
        defense = ((defense) / 1.15 );
        dmg.increase(normal_at);
        dodge = (int)(((double)dodge) * normal_at);
        level++;
    }
};

class Spirit : public Monster {
public:
    

    Spirit(string a, int lvl, int hp , damage_range d, double def , int dod) :Monster(a,lvl,hp,d,def,dod) {
        dodge = (int)(((double)dodge) * better_at);
        for(int i = 0; i < lvl; i++){
            levelUp();
        }
    }

    void printMonster() {
        cout << "Spirit ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;

        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        dmg.print();
        cout << "Defense : " << defense << endl;
        cout << "Dodge : " << dodge << endl;
    }

    void levelUp() {
        max_health = (int)(((double)max_health) * normal_at);
        healthPower = max_health;
        defense = ((defense) / 1.1);
        dmg.increase(normal_at);
        dodge = (int)(((double)dodge) * better_at);
        level++;
    }
};
*/
/*
class block { //foundation for grid 
protected:    
    bool accessible; //if the block is accessible 

public:
    block() {        
        accessible = true;
    }    

    virtual void print() {

    }

    virtual vector<Hero*> getHeros()const{
        vector<Hero*> k;
        return k;
    }

    bool is_accessible()const {
        return accessible;
    }

    virtual void placeHero(Hero *h) {
    }

    virtual void exitHero(Hero *h) {
        
    }

    virtual int entry() {
        return -100;
    }

    virtual bool encounter(){
        return false;
    }

    virtual Market * getMarket()const{
        return nullptr;
    }

};


class common_block : public block  {
private:
    vector<Hero*> hero; //vector of hero pointers 
    probability percent;    //probability of an encounter to happen
public:
    common_block():percent(100), block() {

    }    

    bool encounter(){
        return percent.chance();
    }   
    
    vector<Hero*> getHeros()const{
        return hero;
    } 

    void placeHero(Hero *h) {
        hero.push_back(h);
    }

    void exitHero(Hero *h) {
        auto it = hero.begin(); //iterator pointing at the start 
        while ((*it) != h) { //while the hero is not the one we want to exit 
            it++;   //go to the next iterator 
        }
        hero.erase(it); // erase the hero from the vector 
    }

    void print() {     
        if (hero.size()>0) {
            int i;
            for (i = 0; i < hero.size(); i++) {
                cout << hero[i]->getHeroID() << " ";
            }
            if (i == 1) {
                cout << "    ";
            }
            else if (i == 2) {
                cout << "   ";
            }
            else if (i == 3) {
                cout << " ";
            }
        }
        else {
            cout << "+     ";
        }
    }

    int entry(){
        return 1;
    }    
};

class market_block : public block {
private:
    Market *market; //pointer to market 
    vector<Hero*> hero; //a vector of pointers to hero 
public:
    market_block():block()  {
        market = new Market;
        market->createMarket();
    }    

    int entry(){
        return 2;
    }

    Market * getMarket()const{        
        return market;
    }

    vector<Hero*> getHeros()const{
        return hero;
    } 

    void placeHero(Hero *h) {
        hero.push_back(h);
    }

    void exitHero(Hero *h) {
        auto it = hero.begin();
        while ((*it) != h) {
            it++;
        }
        hero.erase(it);
    }
    
    void print() {
        if (hero.size() > 0) {
            int i;
            for (i = 0; i < hero.size(); i++) {
                cout << hero[i]->getHeroID() << " ";                
            }
            
            if (i == 1) {
                cout << "M   ";
            }
            else if (i == 2) {
                cout << "M  ";
            }
            else if (i == 3) {
                cout << "M ";
            }
        }
        else {
            cout << "M     ";
        }
    }

    ~market_block(){
        delete market;
    }
};

class nonAccesible : public block {
public:
    nonAccesible() :block() {
        accessible = false;
    }    

    void print() {
        cout << "x     ";
    }
};
*/
/*
class MonsterCreation{  
    vector<Monster*>m;
public:
    MonsterCreation(){
       
    }

    static double doubleRand(double fMin, double fMax){ //generates random double from fmin to fmax 
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    vector<Monster*> getMonsters(vector<Hero*>h){
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

    ~MonsterCreation(){
        for(int i = 0; i < m.size(); i++){
            delete m[i];
        }
    }
};

class HeroCreation{
    vector<Hero*> h;

public:
    
    HeroCreation(){

    }

    vector<Hero*> getHeros(int amount){ //create amount heros 
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

    ~HeroCreation(){
        for(int i = 0; i < h.size(); i++){
            delete h[i];
        }
    } 
};
*/

/*

class Grid {    //map 
private:    
    int k; 
    block * grid[length][height]; //example is 10x10

    int battle(vector<Hero*>h){
        MonsterCreation create;
        vector<Monster*>m = create.getMonsters(h);  //get monsters for h hero vector 
        
        int a;
        int player = 0;
        int monster = 0;
        int dead_monsters = 0;
        int dead_h = 0;
        cout << "h size is " << h.size() << endl;

        while(1){
            player = 0; //player's turn 
            monster = 0;//monster's turn 
            if(dead_h !=h.size()){//if at least one hero is alive
                while(player < h.size()){//for each hero 
                    while(h[player]->is_dead() && player < h.size()-1){//if current hero is dead 
                        player++;//next hero's turn 
                    }                    
                    cout << "Player " << player + 1 << " possible actions : " << endl;
                    cout << "1) map \n2) attack \n3) cast \n4)equip \n5) stats \n6) quitGame" << endl;
                    cin >> a;
                    if(a==2){
                        cout << "Which monster to attack?" << endl;
                        int option;
                        cin >> option;
                        while(m[option-1]->is_dead()){// while the monster the player chooses is dead    
                            cout << "Monster is already dead , choose another" << endl;//make him chooose another monster 
                            cin >> option;
                        }                
                        int death= h[player]->attack(m[option-1]);  //if by attacking , the monster dies , int death = 1                
                        if(death == 1){
                            dead_monsters++;
                            cout << "Monster defeated!" <<endl;
                            m[option-1]->die(); //kill the monster 
                            h[player]->awards(); //award player  
                        }
                        player++; // next player                                   
                    }else if(a==1){
                        this->print();
                    }else if(a==4){
                        h[player]->checkInventory(); 
                        cout << "Choose which item to use!" << endl;
                        cin >> k;
                        h[player++]->equipItem(k);  //current player equips item and it is the next player's turn 
                    }else if(a==5){
                        for(int i = 0; i < h.size(); i++){
                            h[i]->printHero();
                            cout << endl;
                        }
                        for(int i = 0;i < m.size(); i++){
                            m[i]->printMonster();
                            cout << endl;
                        }                
                    }else if(a==3){
                        int death;
                        int option;
                        cout << "Which spell to cast?" << endl;
                        h[player]->checkSpells();   //prints spell inventory 
                        cin >> k;   //selects k-th spell 
                        cout << endl;
                        cout << "Which monster to attack?" << endl;
                        cin >> option;
                        while(m[option-1]->is_dead()){  //while the selected monster is dead    
                            cout << "Monster is already dead , choose another" << endl;
                            for(int i = 0; i < m.size();i++){
                                cout << i << ") ";
                                m[i]->printName();
                                cout << endl;
                            }
                            cin >> option;  //select another 
                        }   
                        death = h[player]->spellDamage(k,m[option-1]);  //if by casting the spell , the monster dies , int death = 1
                        if(death == 1){
                            dead_monsters++;
                            cout << "Monster defeated!" << endl;
                            m[option-1]->die();//kill the monster 
                            h[player]->awards();// award the player 
                        } 
                        player++;//next player                
                    }else if(a==6){
                        return -2;
                    }        
                }
            }else{
                cout << "All heroes are dead" << endl; 
                for(int i = 0 ; i < h.size(); i++){
                    h[i]->revive(); //revive them so that they can try play again 
                }
                return -1;
            }
            if(dead_monsters == m.size()){  //if all monsters are dead 
                cout << "All monsters defeated" << endl;
                return 1;
            }else{
                while(monster< h.size()){   //for each monster 
                    while(m[monster]->is_dead() && monster < m.size()-1){ //if selected monster is dead skip its turn                        
                        monster++;
                    }
                    int option = rand()%3;  //select random player 
                    int death = 0;
                    m[monster]->printName();
                    cout << " attacked ";
                    h[option]->printName();
                    cout << endl;
                    
                    death =m[monster++]->attack(h[option]);  //attack player and if player dies , int death = 1
                    if(death == 1){
                        h[option]->die();   //kill the player 
                        h[option]->printName(); 
                        cout << "is dead!" << endl;
                    }                  
                }
            }
            for(int i = 0 ; i< h.size();i++){
                if(!h[i]->is_dead())
                    h[i]->replenish();  //replenish if they are alive 
            }

            for(int i = 0 ; i < m.size(); i++){
                if(!m[i]->is_dead())
                    m[i]->replenish();  //replenish if they are alive 
            }
            
        }
        return 1;
    }

    int marketplace(vector<Hero*>h, Market *market){    
        int option = 1;
        int item= 0;
        int a=0;
        market->printMarket();  // prints the market 

        while(1){   //exit if players says so 
            cout << "Inventory of player " << option << endl;
            cout << h.size() << endl;
            h[option-1]->checkInventory();  //print inventory of selected player
            cout << "Possible actions : \n1) Buy Item\n2) Buy Spell\n3) Sell Item\n4) Sell Spell\n5) Check Inventories\n6) Switch player\n7) Exit" << endl;
            cin >> a;
            if(a == 5){
                h[option-1]->checkInventory();
                market->printMarket();
                continue;
            }else if(a == 6){   // cycle through the players
                if(option < h.size() ){ 
                    option++;
                    continue;
                }else{
                    option = 1;
                    continue;
                }
            }else if(a == 1){
                cout << "Which item to buy ?" << endl;
                cin >> item;    //choose item

                while(item > market->getItemNumber() && item <= 0 ){    // if there is no such item
                    cout << "Invalid Item indicator , choose again!" << endl;
                    cin >> item;    // select another
                }

                Item *it = market->buy_from_market(item);   //return pointer to the item-th item

                if(h[option-1]->buy(it)==0){    //buys the item the pointer "it" points to
                    it->printName();
                    cout << " was bought\n";
                    market->remove(item);   //removes item from market inventory
                }

            }else if(a == 2){
                cout << "Which spell to buy ?" << endl;
                cin >> item;

                while(item > market->getSpellNumber() && item <= 0 ){
                    cout << "Invalid Spell indicator , choose again!" << endl;
                    cin >> item;
                }

                Spell *it = market->buy_spell_from_market(item);

                if(h[option-1]->buy_spell(it)==0){
                    it->printName();
                    cout << " was bought\n";
                    market->remove_spell(item);
                }

            }else if(a == 3){
                cout << "Which Item to sell ? "<< endl;
                cin >> item;

                while(item > h[option-1]->getItemNumber() && item <= 0 ){
                    cout << "Invalid Item indicator , choose again!" << endl;
                    cin >> item;
                }

                h[option-1]->sell(item)->printName();
                cout << " was sold!" << endl;

            }else if(a == 4){
                cout << "Which Spell to sell ? "<< endl;
                cin >> item;

                while(item > h[option-1]->getSpellNumber() && item <= 0 ){
                    cout << "Invalid Spell indicator , choose again!" << endl;
                    cin >> item;
                }

                h[option-1]->sell(item)->printName();
                cout << " was sold!"<< endl;

            }else if(a == 7){
                cout << "Exiting Market" << endl;
                return -1;
            }
        }
        return -1;
    }

    int block_entry(coordinates p1){    //what to do when the heros enter a block
        vector<Hero *> h = grid[p1.x][p1.y]->getHeros();    //current block heros
        if(grid[p1.x][p1.y]->entry()==1 && (p1.x != 0 || p1.y != 0)){   // if the block is a common block and it is not the start of the map
            if(grid[p1.x][p1.y]->encounter()){  //if they encounter monsters 
                return battle(h);   //return the outcome of the battle (1 if heroes won and -1 if monsters won )
            }            
        }else if(grid[p1.x][p1.y]->entry()==2){ // if it is a market block  
                   
            marketplace(h,grid[p1.x][p1.y]->getMarket());

            return 2;
        }
        return 4;
    }

    int move_up(Hero *h) {  //moves a hero up 
        coordinates p1 = h->getCoordinates();
        if (p1.y -1 >= 0 && grid[p1.x][p1.y -1]->is_accessible()) { //if the desired position is accesible and inside the map
            h->move_up();   //move him up
            coordinates p2 = h->getCoordinates();   //get new coordinates 
            int x1 = p1.x;
            int y1 = p1.y;
            int x2 = p2.x;
            int y2 = p2.y;
            grid[x2][y2]->placeHero(h); //place to new block 
            grid[x1][y1]->exitHero(h);  //remove from previous block 
            return 0;
        }
        else {            
            cout << "Try again" << endl;
            return -3;
        }
    }

    int move_down(Hero *h) {    //same as move up
        coordinates p1 = h->getCoordinates();
        if (p1.y + 1 < height && grid[p1.x][p1.y+1]->is_accessible()) {
            h->move_down();
            coordinates p2 = h->getCoordinates();
            int x1 = p1.x;
            int y1 = p1.y;
            int x2 = p2.x;
            int y2 = p2.y;
            cout << "x2 is " << x2 << endl;
            cout << "y2 is " << y2 << endl;
            grid[x2][y2]->placeHero(h);
            grid[x1][y1]->exitHero(h);
            return 0;
        }
        else {
            cout << "Try again" << endl;
            return -3;
        }
    }

    int move_right(Hero *h) {
        coordinates p1 = h->getCoordinates();
        if (p1.x + 1 < length && grid[p1.x+1][p1.y]->is_accessible()) { //same as move up
            h->move_right();
            coordinates p2 = h->getCoordinates();
            int x1 = p1.x;
            int y1 = p1.y;
            int x2 = p2.x;
            int y2 = p2.y;
            
            grid[x2][y2]->placeHero(h);
            grid[x1][y1]->exitHero(h);
            return 0;
        }
        else {
            cout << "Try again" << endl;
            return -3;
        }
    }    

    int move_left(Hero *h) {    //same
        coordinates p1 = h->getCoordinates();
        if (p1.x -1 >= 0 && grid[p1.x-1][p1.y]->is_accessible()) {
            h->move_left();
            coordinates p2 = h->getCoordinates();
            int x1 = p1.x;
            int y1 = p1.y;
            int x2 = p2.x;
            int y2 = p2.y;
            grid[x2][y2]->placeHero(h);
            grid[x1][y1]->exitHero(h);
            return 0;
        }
        else {
            cout << "Try again" << endl;
            return -3;
        }
    }
    
    int move_up(vector<Hero*> h){   //moves all heros up
        for(int i = 0; i < h.size();i++){   //for each hero
            if((move_up(h[i])== 0) && i == h.size() -1){    //if the player can be moved and when all players have been moved 
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1); //do what each block has to do
            }                
        }
        return 3;
    }

    int move_down(vector<Hero*> h){
        for(int i = 0; i < h.size();i++){
            if((move_down(h[i])== 0) && i == h.size() -1){
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1);
            }     
        }
        return 3;
    }

    int move_left(vector<Hero*> h){
        for(int i = 0; i < h.size();i++){
            if((move_left(h[i])== 0) && i == h.size() -1){
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1);
            }     
        }
        return 3;
    }

    int move_right(vector<Hero*> h){
        for(int i = 0; i < h.size();i++){
            if((move_right(h[i])== 0) && i == h.size() -1){
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1);
            }     
        }
        return 3;
    }
    
public:   
    Grid() {    //allocation of a 10x10 block grid 
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                grid[i][j] = new block;
            }
        }  
        k = 0;      
    }  

    void createGrid(vector<Hero*> h) {
        probability nonacc(15); //15% chance for a block to be non accessible        
        probability mark(5);    //5% chance for a block to be a market block
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < height; j++) {
                if (i != 0 && j != 0 && mark.chance()) { // if it is not the starting block , then see if a market block can be created 
                    grid[i][j] = new market_block;
                }
                else if (i != 0 && j != 0 && nonacc.chance() ) {// if it is not the starting block , then see if a non acc block can be created 
                    grid[i][j] = new nonAccesible;
                }else if(i == 1 && j == 0){ //create a market block right next to the heros so that we can test the market
                    grid[i][j] = new market_block;
                }else { // else create a common block
                    grid[i][j] = new common_block;
                }
            }
        }

        for(int i = 0; i < h.size(); i++){            
            grid[0][0]->placeHero(h[i]);    //place heros in the 0,0 block3
        }
    }        

    int play(vector<Hero*> h){
        static int option = 1;
        int a = 0;
        cout << "Current player selected : Player " << option << endl;
        cout << "Perimitted actions : \n1) Map\n2) Up\n3) Down\n4) Left\n5) Right\n6) Switch Player\n7) Check Inventory" <<endl;
        cout << "8) Equip\n9) Stats\n10) Quit Game " << endl;
        cin >> a;
        while(a < 1 || a > 10){
            cout << "Invalid Number" << endl;
            cin >> a;
        }        
            if(a == 1){
                print();
            }else if(a == 2){
                return move_up(h);
            }else if(a == 3){
                return move_down(h);
            }else if( a == 4){
                return move_left(h);
            }else if( a == 5){
                return move_right(h);
            }else if(a == 6){
                if(option < h.size() ){
                    option++;                    
                }else{
                    option = 1;                    
                }
            }else if(a == 7){                
                while(h[option-1]->menu()); 
            }else if(a == 10){
                cout << "Ending Game.." << endl;
                return -2;
            }else if(a == 8){
                h[option -1]->checkInventory();
                cout << "Choose which item to use!" << endl;
                cin >> k;
                h[option-1]->equipItem(k);
            }else if(a ==9){
                h[option -1]->printHero();
                cout << endl;
            }
            return 0;
    }                 

    void print() {
        int k = 0;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < height; j++) {
                grid[j][i]->print();
            }
            cout << endl;
            cout << endl;
        }
    }

    void return_to_start(vector<Hero *> h){
        coordinates p = h[0]->getCoordinates();
        for(int i = 0; i < h.size(); i++){
            grid[0][0]->placeHero(h[i]);
            grid[p.x][p.y]->exitHero(h[i]);
        }
    }

    ~Grid(){
        for(int i = 0; i < length; i++){
            for(int j = 0; j < height; j++){
                delete grid[i][j];
            }
        }
    }
};
*/

int main()
{
    srand(time(NULL));

    HeroCreation createHeros;

    cout << "How many heros do you want to create?" << endl;
    int a;
    cin >> a;

    vector<Hero*> h = createHeros.getHeros(a);  //creating heros

    for(int i = 0; i < a; i++){ //print heros
        cout << "--------------------------------------------------------" << endl;
        h[i]->printHero();
        cout << endl;        
    }
    cout << "--------------------------------------------------------" << endl;


    Grid grid;
    grid.createGrid(h);
    grid.print();  

    while(1){
        int action = grid.play(h);  
        if(action==-2){
            return -2;  // -2 ends game
        }else if(action == 1){
            return 1;    //1 means they won
        }else if(action == -1){ // -1 means they lost 
            grid.return_to_start(h);
            continue;
        }else{
            continue;
        }
    }

    return 0;
}
