using namespace std;


class Market {  //markeplace 
private:
    Inventory *inventory;
public:
    Market() ;

    void createMarket(vector<Item*> item, vector<Spell*> spells) ;

    void createMarket();

    void printMarket() ;

    int getItemNumber()const;

    int getSpellNumber()const;

    Item* buy_from_market(int k);

    Item* remove(int k);

    Spell* buy_spell_from_market(int k);

    Spell *remove_spell(int k);

    ~Market();
};