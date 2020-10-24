#include <cstdlib>
#include "Hero.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Hero::Hero() {
    Hero_name = "";
    Hero_money = 0;
    Hero_influence = 0;
    Hero_army_size = 0;
    Hero_score = 0;
    Hero_location_row = 0;
    Hero_location_column = 0;
    Hero_tiles_controlled = 0;
    for(int i = 0; i < 4; i++)
    {
        Hero_warriors[i] = Warrior();
    }
    Hero_has_ship = false;
    Hero_is_dead = false;
    Hero_controlled_by_player = false;
} //default constructor

Hero::Hero(string namePC, int moneyPC, int influencePC, int army_sizePC, int scorePC, int location_rowPC, int location_columnPC, int tiles_controlledPC, Warrior warriorsPC[4], bool has_shipPC, bool is_deadPC, bool controlledPC) {
    Hero_name = namePC;
    Hero_money = moneyPC;
    Hero_influence = influencePC;
    Hero_army_size = army_sizePC;
    Hero_score = scorePC;
    Hero_location_row = location_rowPC;
    Hero_location_column = location_columnPC;
    Hero_tiles_controlled = tiles_controlledPC;
    for(int i = 0; i < 4; i++)
    {
        Hero_warriors[i] = warriorsPC[i];
    }
    Hero_has_ship = has_shipPC;
    Hero_is_dead = is_deadPC;
    Hero_controlled_by_player = controlledPC;
} //paramaterized constructor

void Hero::Hero_setName(string nameInput) {
    Hero_name = nameInput;
} //set hero name to string input

string Hero::Hero_getName() {
    return Hero_name;
} //return hero name

void Hero::Hero_setMoney(int moneyInput) {
    Hero_money = moneyInput;
} //set money to moneyInput

int Hero::Hero_getMoney() {
    return Hero_money;
} //return hero money

void Hero::Hero_setInfluence(int influenceInput) {
    Hero_influence = influenceInput;
} //set hero influence

int Hero::Hero_getInfluence() {
    return Hero_influence;
} //return hero influence

void Hero::Hero_setArmySize(int armySizeInput) {
    Hero_army_size = armySizeInput;
} //set army size to input

int Hero::Hero_getArmySize() {
    return Hero_army_size;
} //return army size

void Hero::Hero_setScore(int scoreInput) {
    Hero_score = scoreInput;
} //set score to input

int Hero::Hero_getScore() {
    return Hero_score;
} //return score

void Hero::Hero_setWarriors(Warrior warriorInput, int addressInput) {
    if(addressInput >= 0 && addressInput <= 4)
    {
        Hero_warriors[addressInput] = warriorInput;
    }
    else
    {
        return;
    }
} //set warriors at addressInput to warriorInput

Warrior Hero::Hero_getWarriors(int address) {
    if(address >= 0 && address < 4)
    {
        return Hero_warriors[address];
    }
    else
    {
        return Warrior();
    }
} //return warrior at address

void Hero::Hero_setWarriorMorale(int address, int moraleInput) {
    Hero_warriors[address].Warrior_setMorale(moraleInput);
} //set morale for warrior

void Hero::Hero_setWarriorStrength(int address, int strengthInput) {
    Hero_warriors[address].Warrior_setStrength(strengthInput);
} //set strength for warrior

void Hero::Hero_setWarriorLoyalty(int address, int loyaltyInput) {
    Hero_warriors[address].Warrior_setLoyalty(loyaltyInput);
} //set loyalty for warrior

int Hero::Hero_getNumWarriors() {
    int number = 0;
    for(int i = 0; i < 4; i++)
    {
        if(Hero_warriors[i].Warrior_getName() != "" && Hero_warriors[i].Warrior_getName() != " ")
        {
            number++;
        }
    }
    return number;
} //return number of warriors

void Hero::Hero_setLocation_Row(int rowInput) {
    Hero_location_row = rowInput;
} //set hero location row

int Hero::Hero_getLocation_Row() {
    return Hero_location_row;
} //return hero lcoation row

void Hero::Hero_setLocation_Column(int columnInput) {
    Hero_location_column = columnInput;
} //set hero location column

int Hero::Hero_getLocation_Column() {
    return Hero_location_column;
} //return hero location column

void Hero::Hero_set_has_Ship(bool has_shipInput) {
    Hero_has_ship = has_shipInput;
} //set hero has ship

bool Hero::Hero_get_has_Ship() {
    return Hero_has_ship;
} //get hero has ship

void Hero::Hero_set_has_dragonglass(int indexInput, bool dragonglassInput) {
    Hero_warriors[indexInput].Warrior_set_has_dragonglass(dragonglassInput);
} //set hero has dragonglass in party

void Hero::Hero_set_has_wildfire(int indexInput, bool wildfireInput) {
    Hero_warriors[indexInput].Warrior_set_has_wildfire(wildfireInput);
} //set hero has wildfire in party

bool Hero::Hero_can_travel_water() {
    for(int i = 0; i < 4; i++)
    {
        if(Hero_has_ship == true || Hero_warriors[i].Warrior_get_has_ship() == true)
        {
            return true;
        }
        else if(i == 3 && Hero_has_ship == false && Hero_warriors[i].Warrior_get_has_ship() == false)
        {
            return false;
        }
    }
} //return if hero has boat in party

bool Hero::Hero_has_wildfire_in_party() {
    for(int i = 0; i < 4; i++)
    {
        if(Hero_warriors[i].Warrior_get_has_wildfire() == true)
        {
            return true;
        }
        else if(i == 3 && Hero_warriors[i].Warrior_get_has_wildfire() == false)
        {
            return false;
        }
    }
} //return if hero has wildire in party

bool Hero::Hero_has_dragonglass_in_party() {
    for(int i = 0; i < 4; i++)
    {
        if(Hero_warriors[i].Warrior_get_has_dragonglass() == true)
        {
            return true;
        }
        else if(i == 3 && Hero_warriors[i].Warrior_get_has_dragonglass() == false)
        {
            return false;
        }
    }
} //return if hero has dragonglss inparty

void Hero::Hero_set_tiles_controlled() {
    return;
}  //set number of tiles controlled

int Hero::Hero_get_tiles_controlled() {
    return Hero_tiles_controlled;
} //get number of tiles controlled

void Hero::Hero_set_death(bool deathInput) {
    Hero_is_dead = deathInput;
} //set if hero is dead

bool Hero::Hero_get_death() {
    return Hero_is_dead;
} //return if hero is dead

void Hero::Hero_set_is_controlled_by_player(bool controlledInput) {
    Hero_controlled_by_player = controlledInput;
} //set hero is controlled by player

bool Hero::Hero_get_is_controlled_by_player() {
    return Hero_controlled_by_player;
} //return if hero is controlled by player

void Hero::Hero_increaseRow() {
    Hero_location_row = Hero_location_row + 1;
} //increase location row

void Hero::Hero_decreaseRow() {
    Hero_location_row = Hero_location_row - 1;
} //decrease location row

void Hero::Hero_increaseColumn() {
    Hero_location_column = Hero_location_column + 1;
} //increase location column

void Hero::Hero_decreaseColumn() {
    Hero_location_column = Hero_location_column - 1;
} //decrease location column
