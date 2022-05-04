using namespace std;

class Spell {   //spell is not an item
protected:
    name name_Spell;
    int price;  
    int level_exp;  //minimum level
    damage_range dmg;   
    int magic_power;    //magic power cost 
public:
    Spell();

    Spell(int l , int h) ;


    Spell(string a, int p , int l, damage_range d, int mp);
    
    static double doubleRand(double fMin, double fMax);

    int Damage(int dexterity);

    int getMagic()const;

    int getPrice()const;

    int getLevel()const;

    void printName();

    virtual void print();

    virtual void action(damage_range &dmg, int &defense ,int& dodge, int &mana);
};

class Ice_Spell : public Spell {
private:
    double reduce_damage;		

public:

    Ice_Spell(string a, int p, int l, damage_range d, int mp, double r);

    Ice_Spell();

    Ice_Spell(int l , int h, double rdmg) ;

    void print();

    static vector<Ice_Spell*> create(int amount);

    void action(damage_range &dmg, int &defense ,int& dodge, int &mana);

    ~Ice_Spell();

};

class Fire_Spell : public Spell {
private:
    double reduce_defense; 	/* reduce defemse (to the opponent for a couple of rounds) */
public:

    Fire_Spell();

    Fire_Spell(string a, int p , int l , damage_range d , int mp , double r);

    static vector<Fire_Spell*> create(int amount);

    void print();

    void action(damage_range &dmg, double &defense ,int& dodge, int &mana);

    ~Fire_Spell() ;
};

class Lightning_Spell : public Spell {
private:
    double reduce_chance;   /* reduce chance of dodging the attack */
public:
    Lightning_Spell() ;

    Lightning_Spell(double rc);  

    Lightning_Spell(string a, int p , int l , damage_range d , int mp , double r);

    static vector<Lightning_Spell*> create(int amount);

    void print();

    void action(damage_range &dmg, int &defense ,int& dodge, int &mana);

    ~Lightning_Spell();
};