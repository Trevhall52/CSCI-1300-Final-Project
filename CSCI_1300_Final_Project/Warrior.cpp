#include <cstdlib>
#include "Warrior.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Warrior::Warrior() { //default constructor
    Warrior_name = "";
    Warrior_strength = 0;
    Warrior_loyalty = 0;
    Warrior_morale = 0;
    Warrior_is_free = false;
    Warrior_has_ship = false;
    Warrior_has_wildfire = false;
    Warrior_has_dragonglass = false;
    Warrior_locationColumn = 0;
    Warrior_locationRow = 0;
} //default constructor

Warrior::Warrior(string namePC, int strengthPC, int loyaltyPC, int moralePC, bool is_freePC, bool has_shipPC, bool has_wildfirePC, bool has_dragonglassPC) {
    Warrior_name = namePC;
    Warrior_strength = strengthPC;
    Warrior_loyalty = loyaltyPC;
    Warrior_morale = moralePC;
    Warrior_is_free = is_freePC;
    Warrior_has_ship = has_shipPC;
    Warrior_has_wildfire = has_wildfirePC;
    Warrior_has_dragonglass = has_dragonglassPC;
}

void Warrior::Warrior_setName(string nameInput) {
    Warrior_name = nameInput;
} //set warrior name

string Warrior::Warrior_getName() {
    return Warrior_name;
} //return warrior name

void Warrior::Warrior_setStrength(int strengthInput) {
    if(strengthInput >= 0 && strengthInput <= 200)
    {
       Warrior_strength = strengthInput;
    }
    else
    {
        return;
    }
} //set warrror strength

int Warrior::Warrior_getStrength() {
    return Warrior_strength;
} //return warrior strength

void Warrior::Warrior_setLoyalty(int loyaltyInput) {
    if(loyaltyInput >= 0 && loyaltyInput <= 100)
    {
        Warrior_loyalty = loyaltyInput;
    }
    else
    {
        return;
    }
} //set warrior loyalty

int Warrior::Warrior_getLoyalty() {
    return Warrior_loyalty;
} //return warrior loyalty

void Warrior::Warrior_setMorale(int moraleInput) {
    if(moraleInput >= 0 && moraleInput <= 100)
    {
        Warrior_morale = moraleInput;
    }
    else
    {
        return;
    }
} //set warrior morale

int Warrior::Warrior_getMorale() {
    return Warrior_morale;
} //return warrior morale

void Warrior::Warrior_set_is_free(bool is_freeInput) {
    Warrior_is_free = is_freeInput;
} //set warrior is free

bool Warrior::Warrior_get_is_free() {
    return Warrior_is_free;
} //return warrior is free

void Warrior::Warrior_set_has_ship(bool has_shipInput) {
    Warrior_has_ship = has_shipInput;
} //set warrior has ship

bool Warrior::Warrior_get_has_ship() {
    return Warrior_has_ship;
} //return warrior has ship

void Warrior::Warrior_set_has_wildfire(bool has_wildfireInput) {
    Warrior_has_wildfire = has_wildfireInput;
} //set warrior has wildfire

bool Warrior::Warrior_get_has_wildfire() {
    return Warrior_has_wildfire;
} //return warrior hsa wildfire

void Warrior::Warrior_set_has_dragonglass(bool has_dragonglassInput) {
    Warrior_has_dragonglass = has_dragonglassInput;
} //set warrior has dragonglass

bool Warrior::Warrior_get_has_dragonglass() {
    return Warrior_has_dragonglass;
} //get warrior has dragonglass

void Warrior::Warrior_setLocationRow(int rowInput) {
    Warrior_locationRow = rowInput;
} //set location row

void Warrior::Warrior_setLocationColumn(int columnInput) {
    Warrior_locationColumn = columnInput;
} //set location column

int Warrior::Warrior_getLocationRow() {
    return Warrior_locationRow;
} //return location row

int Warrior::Warrior_getLocationColumn() {
    return Warrior_locationColumn;
} //return location column
