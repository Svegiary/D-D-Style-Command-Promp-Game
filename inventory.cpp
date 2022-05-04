#include <iostream>
#include <vector>
#include <cstdlib>
#include "structs.h"
#include "items.h"
#include "spells.h"
#include "inventory.h"

using namespace std;

    Inventory::Inventory() {

    }

    void Inventory::add_to_inventory(Item *t) {
        item.push_back(t);
    }
    void Inventory::add_to_inventory(Spell *s){
        spell.push_back(s);
    }

    Inventory* Inventory::createInventory(){   //creates inventory 
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

    int Inventory::equipItem(int k, int &dmg, double &ar, int &strength , int &agility , int &dexterity) { // equips the k-th item
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

    Spell* Inventory::equipSpell(int k){   // returns a pointer to the k-th spell 
        if(k <= spell.size()){
            return spell[k-1];
        }else{
            cout << "No such spell" << endl;
            return nullptr;
        }
    }

    Item* Inventory::select(int k) {   //returns pointer to the k-th item 
        return item[k - 1];
    }

    Item* Inventory::remove(int k) {   // removes the k-th item 
        Item* it = item[k - 1];
        item.erase(item.begin() + k - 1);        
        return it;
    }

    Spell* Inventory::select_spell(int k){ //returns pointer to the k-th spell 
        return spell[k-1];
    }

    Spell* Inventory::remove_spell(int k){ //removes the k-th spell and returns a pointer to it 
        Spell* it = spell[k - 1];
        spell.erase(spell.begin() + k - 1);        
        return it;
    }

    void Inventory::checkItems() { //prints items 
        cout << "Items are: " << endl;
        for (int i = 0; i < item.size(); i++) {
            cout << i + 1 << ")";
            item[i]->print();
            cout << endl;
        }
    }

    void Inventory::checkSpells(){ //prints spells 
        cout << "Spells are : " << endl;
        for(int i = 0; i < spell.size(); i++){
            cout << i+1<< ")";
            spell[i]->print();
            cout << endl;
        }
    }

    void Inventory::checkInventory(){  //prints inventory 
        checkItems();
        checkSpells();
    }

    int Inventory::menu(int &dmg, double &ar, int &strength , int &agility , int &dexterity){  //inventory menu 
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

    int Inventory::getItemNumber()const{
        return item.size();
    }

    int Inventory::getSpellNumber()const{
        return spell.size();
    }

    Inventory::~Inventory(){
        for(int i =0; i < item.size(); i++){
            delete item[i];
        }
        for(int i = 0; i < spell.size(); i++){
            delete spell[i];
        }
    }