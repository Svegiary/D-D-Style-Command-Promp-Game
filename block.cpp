#include <iostream>
#include <vector>
#include <cstdlib>
#include "constants.h"
#include "probability.h"
#include "structs.h"
#include "items.h"
#include "spells.h"
#include "inventory.h"
#include "market.h"
#include "living.h"
#include "block.h"

using namespace std;

block::block() {        
        accessible = true;
    }    

    void block::print() { 

    }

    vector<Hero*> block::getHeros()const{
        vector<Hero*> k;
        return k;
    }

    bool block::is_accessible()const {
        return accessible;
    }

    void block::placeHero(Hero *h) {
    }

    void block::exitHero(Hero *h) {
        
    }

    int block::entry() {
        return -100;
    }

    bool block::encounter(){
        return false;
    }

    Market * block::getMarket()const{
        return nullptr;
    }

    common_block::common_block():percent(100), block() {

    }    

    bool common_block::encounter(){
        return percent.chance();
    }   
    
    vector<Hero*> common_block::getHeros()const{
        return hero;
    } 

    void common_block::placeHero(Hero *h) {
        hero.push_back(h);
    }

    void common_block::exitHero(Hero *h) {
        auto it = hero.begin(); //iterator pointing at the start 
        while ((*it) != h) { //while the hero is not the one we want to exit 
            it++;   //go to the next iterator 
        }
        hero.erase(it); // erase the hero from the vector 
    }

    void common_block::print() {     
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

    int common_block::entry(){
        return 1;
    }

    market_block::market_block():block()  {
        market = new Market;
        market->createMarket();
    }    

    int market_block::entry(){
        return 2;
    }

    Market * market_block::getMarket()const{        
        return market;
    }

    vector<Hero*> market_block::getHeros()const{
        return hero;
    } 

    void market_block::placeHero(Hero *h) {
        hero.push_back(h);
    }

    void market_block::exitHero(Hero *h) {
        auto it = hero.begin();
        while ((*it) != h) {
            it++;
        }
        hero.erase(it);
    }
    
    void market_block::print() {
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

    market_block::~market_block(){
        delete market;
    }

    nonAccesible::nonAccesible() :block() {
        accessible = false;
    }    

    void nonAccesible::print() {
        cout << "x     ";
    }
