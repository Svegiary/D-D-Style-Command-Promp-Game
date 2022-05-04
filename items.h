/*#include <iostream>
#include <vector>
#include <fstream>
#include "structs.h"
*/

using namespace std;

class Item {    //superclass for items
protected:
    name name_Item; //name
    int price;  //cost  
    int level_exp; //minimum level 
public:

    Item();

    Item(string a, int cost , int level);

    static double doubleRand(double fMin, double fMax);

    virtual int equip(int &dmg, double &armor , int &strength , int &agility, int &dexterity) ;

    int getPrice() const;

    int getLevel()const ;

    virtual void print() ;

    void printName();

};

class Weapon : public Item {
private:
    int damage; //damage 
    int hand_use;   // hand use

public:

    Weapon();

    Weapon(int dmg, int hu);

    Weapon(string s , int dmg , int hu , int cost , int min_lvl);

    static vector<Weapon*> create(int amount);

    int getDamage()const;

    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity);

    int getHandUse()const;    

    void print();    

    ~Weapon();
};

class Armor : public Item {
private:
    double reduce_damage;	 /* reduce damage taken (to the Hero) */

public:

    Armor() ;

    Armor(string s , int cost , int min_level, double reduce);
    static vector<Armor*> create(int amount);
    double getRD() const;
    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity);
    void print();    

    ~Armor();
};

class Potion : public Item {
protected:
     double upgrade;
public:  

    Potion();

    Potion(string a , double i, int cost, int level);

    virtual int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity);

    ~Potion();

};

class DexterityPotion: public Potion{
public:

    DexterityPotion();

    DexterityPotion(string a , double i, int c, int l);   

    void print();

    static vector<DexterityPotion*> create(int amount);

    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity);
};

class AgilityPotion: public Potion{
public:
    AgilityPotion();
    AgilityPotion(string a , double i, int c, int l);
    void print();
    static vector<AgilityPotion*> create(int amount);
    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity);
};

class StrengthPotion : public Potion{
public:

    StrengthPotion();

    StrengthPotion(string a , double i, int c, int l);


    void print();

    static vector<StrengthPotion*> create(int amount);


    int equip(int& extra_dmg, double &armor, int &strength , int &agility, int &dexterity);
};