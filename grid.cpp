#include <iostream>
#include <vector>
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



int Grid::battle(vector<Hero*>h){
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

    int Grid::marketplace(vector<Hero*>h, Market *market){    
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

    int Grid::block_entry(coordinates p1){    //what to do when the heros enter a block
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

    int Grid::move_up(Hero *h) {  //moves a hero up 
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

    int Grid::move_down(Hero *h) {    //same as move up
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

    int Grid::move_right(Hero *h) {
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

    int Grid::move_left(Hero *h) {    //same
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
    
    int Grid::move_up(vector<Hero*> h){   //moves all heros up
        for(int i = 0; i < h.size();i++){   //for each hero
            if((move_up(h[i])== 0) && i == h.size() -1){    //if the player can be moved and when all players have been moved 
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1); //do what each block has to do
            }                
        }
        return 3;
    }

    int Grid::move_down(vector<Hero*> h){
        for(int i = 0; i < h.size();i++){
            if((move_down(h[i])== 0) && i == h.size() -1){
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1);
            }     
        }
        return 3;
    }

    int Grid::move_left(vector<Hero*> h){
        for(int i = 0; i < h.size();i++){
            if((move_left(h[i])== 0) && i == h.size() -1){
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1);
            }     
        }
        return 3;
    }

    int Grid::move_right(vector<Hero*> h){
        for(int i = 0; i < h.size();i++){
            if((move_right(h[i])== 0) && i == h.size() -1){
                coordinates p1 = h[0]->getCoordinates();
                return block_entry(p1);
            }     
        }
        return 3;
    }

    Grid::Grid() {    //allocation of a 10x10 block grid 
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                grid[i][j] = new block;
            }
        }  
        k = 0;      
    }  

    void Grid::createGrid(vector<Hero*> h) {
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

    int Grid::play(vector<Hero*> h){
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

    void Grid::print() {
        int k = 0;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < height; j++) {
                grid[j][i]->print();
            }
            cout << endl;
            cout << endl;
        }
    }

    void Grid::return_to_start(vector<Hero *> h){
        coordinates p = h[0]->getCoordinates();
        for(int i = 0; i < h.size(); i++){
            grid[0][0]->placeHero(h[i]);
            grid[p.x][p.y]->exitHero(h[i]);
        }
    }

    Grid::~Grid(){
        for(int i = 0; i < length; i++){
            for(int j = 0; j < height; j++){
                delete grid[i][j];
            }
        }
    }