#include <iostream>
#include <vector>
#include "constants.h"
#include "probability.h"
#include "structs.h"
#include "items.h"
#include "spells.h"
#include "inventory.h"
#include "living.h"

using namespace std;

Living::Living() {
        level = 1;
        nam.a = "Default Living";
        healthPower = 200;
        dead = false;
        max_health = healthPower;
    }  

    Living::Living(string a) {
        level = 1;
        nam.a = a;
        healthPower = 200;
        dead = false;
        max_health = 200;
    }  

    Living::Living(string a, int lvl , int hp){
        level = 0;
        nam.a = a;
        max_health = hp;
        healthPower = hp;
        dead = false;
    } 

    void Living::nameHero(string a) {
        nam.a = a;
    }

    int Living::getLevel()const {
        return level;
    }

    int Living::getHP()const {
        return healthPower;
    }

    void Living::setlevel(int l) {
        level = l;
    }

    void Living::setHP(int hp){
        healthPower = hp;
    } 

    //virtual functions explained later....................

    int Living::Damage() {
        return -1;
    }

    bool Living::dodged() {
        return -1;
    }

    int Living::is_hurt_by(Living* l) {
        this->healthPower -= l->Damage();
        return -1;
    }

    int Living::getHeroID()const {
        return -2;
    }

    int Living::attack(Living* l) {
        return -2;
    }

    void Living::printMonster() {

    }

    int Living::is_hurt_by_spell(Living *l, int k){
        return -100;
    }

    int Living::is_hurt_by_weapon(Living *l){
        return -100;
    }

    void Living::equipItem(int k){

    }

    Spell* Living::equipSpell(){
        return nullptr;
    }

    void Living::printHero() {

    }

    int Living::spellDamage(int k, Living *l){
        return -100;
    }

    void Living::spellAction(){

    }

    int Living::getDodge()const{
        return -2;
    }

    int Living::getDefense()const{
        return -2;
    }

    damage_range Living::getDmgRange(){
        damage_range dm(0,0);
        return dm;
    }

    void Living::setDmgRange(damage_range dm){

    }

    void Living::setDefense(int d){

    }

    void Living::setDodge(int d){

    }

    void Living::checkItems(){

    }

    void Living::checkSpells(){

    }

    void Living::replenish(){

    }

    //...............................................................................

    bool Living::is_dead(){ //checks if a living is dead 
        return dead;
    }

    void Living::die(){ //kills a living 
        dead = true;
    }

    void Living::printName(){   //prints just the name 
        nam.printName();        
    }

    Living::~Living() {
        
    }

    Monster::Monster() :Living(), dmg(80, 100) {
        defense = 0.9;
        dodge = 100;
    }

    Monster::Monster(string a) :Living(a), dmg(80, 100) {
        defense = 0.9;
        dodge = 100;
    }

    Monster::Monster(string a, int lvl, int hp, damage_range d, double def , int dod):dmg(d),Living(a,lvl,hp){
        level = 0;
        defense = def;
        dodge = dod;               
    }

    int Monster::Damage() {  //calculates (random) number withing the damage range 
        return rand() % (dmg.high - dmg.low + 1) + dmg.low;
    }

    int Monster::getDefense() const {
        return defense;
    }

    int Monster::getDodge() const{
        return dodge;
    }

    damage_range Monster::getDmgRange(){
        return dmg;
    }

    void Monster::setDmgRange(damage_range dm){
        dmg = dm;
    }

    void Monster::setDefense(int d){
        defense = d;
    }

    void Monster::setDodge(int d){
        dodge = d;
    }
    
    bool Monster::dodged() { //calculates if the attack is dodged 
        int p = (int)(dodge / 10);  // dodge is <1000 so p <100 and >0
        probability per(p);
        return per.chance();
    }

    int Monster::attack(Living* l) { //monster attacks 
        if (l->dodged()) {  //if the attack was dodged 
            cout << "Attack dodged" << endl;
            return -1;
        }
        else {
            l->is_hurt_by(this);    //l is hurt by this monster 
            cout << "Hero wounded" << endl;
            if (l->getHP() <= 0) {  //if hp < 0
                cout << "Hero defeated" << endl;
                return 1;
            }
            else {
                return 0;
            }
        }
    }

    void Monster::replenish(){
        healthPower += 30;
    }

    void Monster::printMonster() {

    }

    int Monster::is_hurt_by_weapon(Living* h) {  //monster is hurt by weapon 
        int hp_reduction = (int) ( (double)h->Damage() )* (defense); // defense is double <1 and > 0
        healthPower -= hp_reduction;
        return healthPower;
    }

    int Monster::is_hurt_by_spell(Living *h, int k){ //monster is hurt by k-th spell 
        int hp_reduction = (int) ( (double)h->spellDamage(k,this) )* (defense); // same as before 
        healthPower -= hp_reduction;
        return healthPower;
    }

    Hero::Hero():Living() {
        magicPower = 100;
        strength = 100;
        dexterity = 100;
        agility = 100;
        money = 0;
        xp = 0;      
        weapon_damage = 2; 
        armor_multiplier = 1.0;
        hero_id = 0;
        level_up_xp = level*100;
        monsters_defeated=0;
        money_awarded = 0;
        xp_awarded = 0;
        inventory = new Inventory;
    }

    Hero::Hero(string a,int l,int hp,int s,int d, int ag, int id ):Living(a,l,hp){
        magicPower = 100;
        strength = s;
        dexterity = d;
        agility = ag;
        money = 1000;
        xp = 1;
        weapon_damage = 2;
        armor_multiplier = 1.0;
        hero_id = id;
        level_up_xp = (level+1)*100;
        monsters_defeated = 0;
        money_awarded = 0;
        xp_awarded = 0;
        inventory = new Inventory;
    }    

    int Hero::Damage() {  //adds weapon damage to hero strength 
        return weapon_damage + strength;
    }   

    Spell* Hero::equipSpell(int k){   //equip the k-th spell from the heros inventory and returns a pointer to it       
       return inventory->equipSpell(k);
    }

    int Hero::spellDamage(int k, Monster *m){ //applies spell effects on monster and then it calculates the health to be deducted 
        Spell *s = equipSpell(k);
        magicPower -= s->getMagic();    // deducts magic power cost
        damage_range dm; dm.low = m->getDmgRange().low;
        dm.high = m->getDmgRange().high;
        int defense = m->getDefense();
        int dodge = m->getDodge();
        s->action(dm, defense, dodge,magicPower);   //applies spell effects 

        m->setDmgRange(dm);
        m->setDefense(defense);
        m->setDodge(dodge);
        return s->Damage(dexterity);    //returns damage calculated with dexterity in mind 
    }

    coordinates Hero::getCoordinates()const {
        return position;    
    }

    int Hero::getHeroID()const {   
        return hero_id;
    }

    int Hero::buy(Item *t) {  //buys item
        if (money >= t->getPrice() && level >= t->getLevel()) {    //if they have enough money and level 
            inventory->add_to_inventory(t); //add to hero's inventory 
            money -= t->getPrice(); // deduct cost 
            return 0;
        }
        else if(money < t->getPrice()){ // if the hero does not have enough money 
            cout << "Not enough money\n" << endl;
            return -1;
        }else{
            cout << "Not high enough level" << endl;
            return -1;
        }
    }

    int Hero::buy_spell(Spell *s){    //buys spell 
        if (money >= s->getPrice() && level >= s->getLevel()) { //if they have enough money and are high enough level
            inventory->add_to_inventory(s); // // add spell to inventory 
            money -= s->getPrice(); //deduct cost
            return 0;
        }
        else if(money < s->getPrice()){
            cout << "Not enough money\n" << endl;
            return -1;
        }else{
            cout << "Not high enough level" << endl;
            return -1;
        }
    }

    int Hero::getItemNumber()const{
        return inventory->getItemNumber();
    }

    int Hero::getSpellNumber()const{
        return inventory->getSpellNumber();
    }

    Item * Hero::sell(int k) {    //sell item
        money = money + (inventory->select(k)->getPrice()/2);   //gets paid 
        cout << "Item sold for " << inventory->select(k)->getPrice() / 2 << endl;   
        Item *t = inventory->remove(k); //remove 
        return t;   //return pointer to item 
    }

    Spell* Hero::sell_spell(int k){   //sell spell , same as item 
        money = money + (inventory->select_spell(k)->getPrice()/2);
        cout << "Item sold for " << inventory->select(k)->getPrice() / 2 << endl;
        Spell* s = inventory->remove_spell(k);
        return s;
    }

    bool Hero::dodged() { 
        int p = (int)(agility / 10);
        probability per(p);
        return per.chance();
    }

    //..................movement..........................

    bool Hero::move_up(){ //moves hero up
        if (position.y -1 >= 0) {   //if he can move up 
            position.y -= 1;    // reduce y value 
            return true;    // he did move up 
        }
        else {
            cout << "End of map" << endl;
            return false;   // he did not move up
        }        
    }

    bool Hero::move_right(){
        if (position.x + 1 < length) {
            position.x += 1;
            return true;
        }
        else {
            cout << "End of map" << endl;
            return false;
        }        
    }

    bool Hero::move_down() {
        if (position.y + 1 < height ) {
            position.y += 1;
            return true;
        }
        else {
            cout << "End of map" << endl;
            return false;
        }
    }

    bool Hero::move_left() {
        if ( position.x - 1 >= 0) {
            position.x -= 1;
            return true;
        }
        else {
            cout << "End of map" << endl;
            return false;
        }
    }
    //.............................................

    void Hero::equipItem(int k) { // equips k-th item and applies effects 
        inventory->equipItem(k, weapon_damage, armor_multiplier, strength , agility , dexterity);
    }

    void Hero::checkInventory() { //prints inventory 
        inventory->checkInventory();
    }

    void Hero::checkItems(){  // checks only items 
        inventory->checkItems();
    }

    void Hero::checkSpells(){ //checks only spells 
        inventory->checkSpells();
    }

    int Hero::menu(){ 
        return inventory->menu(weapon_damage, armor_multiplier, strength , agility , dexterity);
    }

    void Hero::printHero() {

    }

    int Hero::castSpell(Living *l, int k){    //casts spell 
        if (l->dodged()) {
            cout << "Spell dodged" << endl;
            return -1;
        }
        else {
            l->is_hurt_by_spell(this, k);
            cout << "Enemy wounded" << endl;
            if (l->getHP() <= 0) {
                cout << "Enemy defeated" << endl;
                return 1;
            }
            else {
                return 0;
            }
        }
    }   

    int Hero::attack(Living *l) {
        if (l->dodged()) {
            cout << "Attack dodged" << endl;
            return -1;
        }
        else {
            l->is_hurt_by_weapon(this);
            cout << "Enemy wounded" << endl;
            if (l->getHP() <= 0) {
                cout << "Enemy defeated" << endl;
                return 1;
            }
            else {
                return 0;
            }
        }
    }

    int Hero::is_hurt_by(Living *l) {
        int hp_reduction = (int)((double)l->Damage() * armor_multiplier);
        healthPower -= hp_reduction;
        return healthPower;
    }

    void Hero::levelUp(){

    }

    void Hero::replenish(){   //replenishes health and magic power 
        magicPower += 20;
        healthPower += 30;
    }

    void Hero::die(){ //if they die 
        money = money/2;    //reduce money 
        dead = true;    //kill them 
    }
    
    void Hero::revive(){
        dead = false;
    }

    void Hero::awards(){  //awards for killing monsters 
        monsters_defeated++;    //increase number of monsters defeated 
        money_awarded = (100*((double)level*1.5))*monsters_defeated;
        xp_awarded = (100*((double)level*1.2))*monsters_defeated;
        xp += xp_awarded;
        money += money_awarded;
        if(xp >= level_up_xp){
            cout << "Level up!!" << endl;
            levelUp();
        }
    }    

    Hero::~Hero(){
        delete inventory;
    }

    Warrior::Warrior(string a,int l,int hp,int s,int d, int ag , int id):Hero(a,l,hp,s,d,ag,id){
        //.............make them better at...............
        strength = (int)(((double)strength) * better_at); 
        agility = (int)(((double)agility) * better_at);
        //...............................................   
        for(int i = 0; i < l; i++){ //get warrior up to level 
            levelUp();
        }     
    }

    void Warrior::printHero() {
        cout << "Warrior ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;
        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        cout << "Strength : " << strength << endl;
        cout << "Magic Power : " << magicPower << endl;
        cout << "Dexterity : " << dexterity << endl;
        cout << "Agility : " << agility << endl;
        cout << "Money : " << money << endl;
        cout << "XP : " << xp << endl;
    }
   
    void Warrior::levelUp() {    // level up
        max_health = (int)(((double)max_health) * normal_at);
        max_magic = (int)(((double)magicPower) * normal_at);
        healthPower = max_health;
        magicPower = max_magic;
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * normal_at);
        agility = (int)(((double)agility) * better_at);
        money += level_up_money;
        level++;
        if(xp < level_up_xp * level){
            xp = level_up_xp * level;
        }
    }

    Paladin::Paladin():Hero() {
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * better_at);
        money = 0;
        xp = 0;
    }   

    Paladin::Paladin(string a,int l,int hp,int s,int d, int ag , int id):Hero(a,l,hp,s,d,ag,id){
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * better_at);   
        for(int i = 0; i < l; i++){
            levelUp();
        }     
    }

    void Paladin::printHero() {
        cout << "Paladin ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;
        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        cout << "Strength : " << strength << endl;
        cout << "Magic Power : " << magicPower << endl;
        cout << "Dexterity : " << dexterity << endl;
        cout << "Agility : " << agility << endl;
        cout << "Money : " << money << endl;
        cout << "XP : " << xp << endl;
    }

    void Paladin::levelUp() {
        max_health = (int)(((double)max_health) * normal_at);
        max_magic = (int)(((double)magicPower) * normal_at);
        healthPower = max_health;
        magicPower = max_magic;
        strength = (int)(((double)strength) * better_at);
        dexterity = (int)(((double)dexterity) * better_at);
        agility = (int)(((double)agility) * normal_at);
        money += level_up_money;
        level++;
        if(xp < level_up_xp * level){
            xp = level_up_xp * level;
        }
        
    }

    Sorcerer::Sorcerer(string a,int l,int hp,int s,int d, int ag, int id ){
        //................make them better at..............
        dexterity = (int)(((double)dexterity) * better_at);
        agility = (int)(((double)agility) * better_at);
        //.................................................
        for(int i = 0; i < l; i++){
            levelUp();
        } 
    }

    void Sorcerer::printHero() {
        cout << "Sorcerer ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;
        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        cout << "Strength : " << strength << endl;
        cout << "Magic Power : " << magicPower << endl;
        cout << "Dexterity : " << dexterity << endl;
        cout << "Agility : " << agility << endl;
        cout << "Money : " << money << endl;
        cout << "XP : " << xp << endl;
    }

    void Sorcerer::levelUp(){
        magicPower = (int)(((double)magicPower) * normal_at);
        strength = (int)(((double)strength) * normal_at);
        dexterity = (int)(((double)dexterity) * better_at);
        agility = (int)(((double)agility) * better_at);
        money += level_up_money;
        level++;
        if(xp < level_up_xp * level){
            xp = level_up_xp * level;
        }
    }

    Dragon::Dragon() {
        dmg.increase(better_at);
    }

    Dragon::Dragon(string a) :Monster(a) {
        dmg.increase(better_at);    
    }

    Dragon::Dragon(string a, int lvl,int hp , damage_range d, double def , int dod) :Monster(a,lvl,hp,d,def,dod) {
        dmg.increase(better_at);  //increase damage range    
        for(int i = 0; i < lvl; i++){   // up to desired level 
            levelUp();
        }
    }

    void Dragon::printMonster() {
        cout << "Dragon "; 
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;

        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        dmg.print();
        cout << "Defense : " << defense << endl;
        cout << "Dodge : " << dodge << endl;
    }  

    void Dragon::levelUp() {        
        max_health = (int)(((double)max_health) * normal_at);
        healthPower = max_health;
        dmg.increase(better_at);
        defense = ((defense) / 1.05);
        dodge = (int)(((double)dodge) * normal_at);
        level++;
    }

    Exoskeleton::Exoskeleton() :Monster() {
        defense =((defense) / 1.15);
    }    

    Exoskeleton::Exoskeleton(string a, int lvl ,int hp, damage_range d, double def , int dod) :Monster(a,lvl,hp,d,def,dod) {
        defense = ((defense) / 1.15);   //decrease defense multiplier so decrease incoming damage 
        for(int i = 0; i < lvl; i++){
            levelUp();
        }
    }

    void Exoskeleton::printMonster() {
        cout << "Exoskeleton ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;

        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        dmg.print();
        cout << "Defense : " << defense << endl;
        cout << "Dodge : " << dodge << endl;
    }

    void Exoskeleton::levelUp() {
        max_health = (int)(((double)max_health) * normal_at);
        healthPower = max_health;
        defense = ((defense) / 1.15 );
        dmg.increase(normal_at);
        dodge = (int)(((double)dodge) * normal_at);
        level++;
    }

    Spirit::Spirit(string a, int lvl, int hp , damage_range d, double def , int dod) :Monster(a,lvl,hp,d,def,dod) {
        dodge = (int)(((double)dodge) * better_at);
        for(int i = 0; i < lvl; i++){
            levelUp();
        }
    }

    void Spirit::printMonster() {
        cout << "Spirit ";
        nam.printName(); cout << ":";
        if(is_dead())
            cout << "**DEAD**";
        cout << endl;

        cout << "Level " << level << endl;
        cout << "HP : " << healthPower << endl;
        dmg.print();
        cout << "Defense : " << defense << endl;
        cout << "Dodge : " << dodge << endl;
    }

    void Spirit::levelUp() {
        max_health = (int)(((double)max_health) * normal_at);
        healthPower = max_health;
        defense = ((defense) / 1.1);
        dmg.increase(normal_at);
        dodge = (int)(((double)dodge) * better_at);
        level++;
    }