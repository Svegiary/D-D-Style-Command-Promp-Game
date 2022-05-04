using namespace std;

class Inventory {
    vector<Item*> item;
    vector<Spell*>spell;
public:
    Inventory();

    void add_to_inventory(Item *t);

    void add_to_inventory(Spell *s);

    Inventory* createInventory();

    int equipItem(int k, int &dmg, double &ar, int &strength , int &agility , int &dexterity) ;

    Spell* equipSpell(int k);

    Item* select(int k);
;
    Item* remove(int k);

    Spell* select_spell(int k);

    Spell* remove_spell(int k);

    void checkItems() ;

    void checkSpells();

    void checkInventory();

    int menu(int &dmg, double &ar, int &strength , int &agility , int &dexterity);

    int getItemNumber()const;

    int getSpellNumber()const;

    ~Inventory();
};