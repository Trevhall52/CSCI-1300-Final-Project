#ifndef HERO_H
#define HERO_H

#include <string>
#include "Warrior.h"
//#include "Tile.h"
//#include "Map.h"

using namespace std;

class Hero
{
public:
    Hero();
    Hero(string namePC, int moneyPC, int influencePC, int army_sizePC, int scorePC, int location_rowPC, int location_columnPC, int tiles_controlledPC, Warrior warriorsPC[4], bool has_shipPC, bool is_deadPC, bool controlledPC);
    void Hero_setName(string nameInput);
    string Hero_getName();
    void Hero_setMoney(int moneyInput);
    int Hero_getMoney();
    void Hero_setInfluence(int influenceInput);
    int Hero_getInfluence();
    void Hero_setArmySize(int armySizeInput);
    int Hero_getArmySize();
    void Hero_setScore(int scoreInput);
    int Hero_getScore();
    void Hero_setWarriors(Warrior warriorInput, int addressInput);
    Warrior Hero_getWarriors(int address);
    void Hero_setWarriorMorale(int address, int moraleInput);
    void Hero_setWarriorStrength(int address, int strengthInput);
    void Hero_setWarriorLoyalty(int address, int loyaltyInput);
    int Hero_getNumWarriors();
    void Hero_setLocation_Row(int rowInput);
    int Hero_getLocation_Row();
    void Hero_setLocation_Column(int columnInput);
    int Hero_getLocation_Column();
    void Hero_set_has_Ship(bool has_shipInput);
    bool Hero_get_has_Ship();
    void Hero_set_has_dragonglass(int indexInput, bool dragonglassInput);
    void Hero_set_has_wildfire(int indexInput, bool wildfireInput);
    bool Hero_can_travel_water();
    bool Hero_has_wildfire_in_party();
    bool Hero_has_dragonglass_in_party();
    void Hero_set_tiles_controlled(); //
    int Hero_get_tiles_controlled();
    void Hero_set_death(bool deathInput);
    bool Hero_get_death();
    void Hero_set_is_controlled_by_player(bool controlledInput);
    bool Hero_get_is_controlled_by_player();
    void Hero_increaseRow();
    void Hero_decreaseRow();
    void Hero_increaseColumn();
    void Hero_decreaseColumn();
private:
    string Hero_name;
    int Hero_money;
    int Hero_influence;
    int Hero_army_size;
    int Hero_score;
    int Hero_location_row;
    int Hero_location_column;
    int Hero_tiles_controlled;
    Warrior Hero_warriors[4];
    bool Hero_has_ship;
    bool Hero_is_dead;
    bool Hero_controlled_by_player;
};

#endif
