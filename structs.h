struct name {   // struct for name
    std::string a;
    void printName() ;   
};

struct damage_range {   // strust for damage range
    int low;    
    int high;

    damage_range();

    damage_range(int l, int h) ;

    damage_range(damage_range &d);

    void increase(double i); //increases damage range

    void decrease(double i);  //decreases damage range     

    void print();
};

struct coordinates {    //coordinates 
    int x;
    int y;

    coordinates() ;
};