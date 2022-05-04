#include <iostream>
#include <vector>
#include <cstdlib>
#include "structs.h"
#include "items.h"
#include "spells.h"
#include "inventory.h"
#include "market.h"

using namespace std;

Market::Market() {
        inventory = new Inventory;
    }

    void Market::createMarket(vector<Item*> item, vector<Spell *> spells) { // creates market from two vectors 
        for (int i = 0; i < item.size(); i++) {
            inventory->add_to_inventory(item[i]);
        }
        for(int i = 0; i < spells.size(); i++){
            inventory->add_to_inventory(spells[i]);
        }
    }

    void Market::createMarket(){    //creates inventory using the creation tool from the inventory 
        inventory->createInventory();
    }

    void Market::printMarket() {
        inventory->checkItems();
        inventory->checkSpells();
    }

    int Market::getItemNumber()const{
        return inventory->getItemNumber();
    }

    int Market::getSpellNumber()const{
        return inventory->getSpellNumber();
    }

    Item* Market::buy_from_market(int k) {  // returns a pointer to the k-th item  
        return inventory->select(k);
    }   

    Item* Market::remove(int k){    //removes item from vector and returns a pointer to it 
        return inventory->remove(k);
    }

    Spell* Market::buy_spell_from_market(int k){    //returns a pointer to the k-th spell
        return inventory->equipSpell(k);
    }

    Spell *Market::remove_spell(int k){ //removes spell from vector and returns a pointer to it 
        return inventory->remove_spell(k);
    }

    Market::~Market(){
        delete inventory;
    }