/*#include <iostream>
#include <vector>
#include "probability.h"
#include "living.h"
#include "market.h"
using namespace std;
*/

using namespace std;

class block { //foundation for grid 
protected:    
    bool accessible; //if the block is accessible

public:
    block();

    virtual void print();
 
    virtual vector<Hero*> getHeros()const;

    bool is_accessible()const ;

    virtual void placeHero(Hero *h) ;

    virtual void exitHero(Hero *h) ;

    virtual int entry() ;

    virtual bool encounter();

    virtual Market * getMarket()const;

};


class common_block : public block  {
private:
    vector<Hero*> hero; //vector of hero pointers 
    probability percent;    //probability of an encounter to happen
public:
    common_block();

    bool encounter();
    
    vector<Hero*> getHeros()const;

    void placeHero(Hero *h) ;

    void exitHero(Hero *h) ;

    void print() ;

    int entry();
};

class market_block : public block {
private:
    Market *market; //pointer to market 
    vector<Hero*> hero; //a vector of pointers to hero 
public:
    market_block();

    int entry();

    Market * getMarket()const;

    vector<Hero*> getHeros()const;

    void placeHero(Hero *h) ;

    void exitHero(Hero *h) ;
    
    void print() ;

    ~market_block();
};

class nonAccesible : public block {
public:
    nonAccesible() ;

    void print();
};