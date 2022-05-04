/*#include<iostream>
#include <vector>
#include <cstdlib>
#include "constants.h"
#include "structs.h"
#include "items.h"
#include "spells.h"
#include "living.h"
#include "block.h"
#include "creation.h"
*/
using namespace std;
class Grid {    //map 
private:    
    int k; 
    block * grid[length][height]; //example is 10x10

    int battle(vector<Hero*>h);

    int marketplace(vector<Hero*>h, Market *market);

    int block_entry(coordinates p1);
    
    int move_up(Hero *h);

    int move_down(Hero *h) ;

    int move_right(Hero *h); 

    int move_left(Hero *h) ;
    
    int move_up(vector<Hero*> h);

    int move_down(vector<Hero*> h);

    int move_left(vector<Hero*> h);

    int move_right(vector<Hero*> h);
    
public:   
    Grid() ;

    void createGrid(vector<Hero*> h);        

    int play(vector<Hero*> h);      

    void print() ;

    void return_to_start(vector<Hero *> h);

    ~Grid();
};