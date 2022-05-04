using namespace std;
class Living {  //Living base class
protected:        
    name nam;
    int level;
    int healthPower;
    bool dead;
    int max_health;
public:
    Living() ;  

    Living(string a) ;

    Living(string a, int lvl , int hp);

    void nameHero(string a) ;

    int getLevel()const;

    int getHP()const ;

    void setlevel(int l);

    void setHP(int hp);

    //virtual functions explained later....................

    virtual int Damage() ;

    virtual bool dodged();

    virtual int is_hurt_by(Living* l) ;

    virtual int getHeroID()const ;

    virtual int attack(Living* l) ;

    virtual void printMonster() ;

    virtual int is_hurt_by_spell(Living *l, int k);

    virtual int is_hurt_by_weapon(Living *l);

    virtual void equipItem(int k);

    virtual Spell* equipSpell();

    virtual void printHero() ;

    virtual int spellDamage(int k, Living *l);

    virtual void spellAction();

    virtual int getDodge()const;

    virtual int getDefense()const;

    virtual damage_range getDmgRange();

    virtual void setDmgRange(damage_range dm);

    virtual void setDefense(int d);

    virtual void setDodge(int d);

    virtual void checkItems();

    virtual void checkSpells();

    virtual void replenish();

    //...............................................................................

    bool is_dead();

    virtual void die();

    void printName();

    ~Living() ;
};

class Monster : public Living { // monster 
protected:
    damage_range dmg;
    double defense;
    int dodge;
public:
    Monster();

    Monster(string a) ;

    Monster(string a, int lvl, int hp, damage_range d, double def , int dod);

    int Damage();

    int getDefense() const ;

    int getDodge() const;

    damage_range getDmgRange();

    void setDmgRange(damage_range dm);

    void setDefense(int d);

    void setDodge(int d);
    
    bool dodged() ;

    int attack(Living* l) ;

    void replenish();

    virtual void printMonster() ;

    int is_hurt_by_weapon(Living* h);

    int is_hurt_by_spell(Living *h, int k);
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

    Hero();

    Hero(string a,int l,int hp,int s,int d, int ag, int id );

    int Damage() ;

    Spell* equipSpell(int k);

    int spellDamage(int k, Monster *m);

    coordinates getCoordinates()const ;

    int getHeroID()const ;

    int buy(Item *t) ;

    int buy_spell(Spell *s);

    int getItemNumber()const;

    int getSpellNumber()const;

    Item * sell(int k) ;

    Spell* sell_spell(int k);

    bool dodged() ;

    //..................movement..........................

    bool move_up();

    bool move_right();

    bool move_down() ;

    bool move_left();
    //.............................................

    void equipItem(int k) ;

    void checkInventory() ;

    void checkItems();

    void checkSpells();

    int menu();

    virtual void printHero();

    int castSpell(Living *l, int k);

    int attack(Living *l);

    int is_hurt_by(Living *l);

    virtual void levelUp();

    void replenish();

    void die();
    
    void revive();

    void awards();

    ~Hero();
};

class Warrior : public Hero {
public:
    

    Warrior(string a,int l,int hp,int s,int d, int ag , int id);

    void printHero();
   
    void levelUp();
};

class Sorcerer :public Hero {
public:     

    Sorcerer(string a,int l,int hp,int s,int d, int ag, int id );

    void printHero() ;

    void levelUp();
};

class Paladin :public Hero {
public:
    Paladin() ;

    Paladin(string a,int l,int hp,int s,int d, int ag , int id);

    void printHero() ;

    void levelUp() ;
};

class Dragon :public Monster {
public:
    Dragon() ;

    Dragon(string a) ;

    Dragon(string a, int lvl,int hp , damage_range d, double def , int dod);

    void printMonster() ;

    void levelUp();
};

class Exoskeleton : public Monster {
public:
    Exoskeleton() ;

    Exoskeleton(string a, int lvl ,int hp, damage_range d, double def , int dod);

    void printMonster();

    void levelUp() ;
};

class Spirit : public Monster {
public:

    Spirit(string a, int lvl, int hp , damage_range d, double def , int dod);

    void printMonster();

    void levelUp() ;
};