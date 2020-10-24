#include <cstdlib>
#include "Tile.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Tile::Tile() {
    Tile_type = 0;
    Tile_letter = ' ';
    Tile_name = "";
    Tile_money = 0;
    Tile_army_size = 0;
    Tile_points = 0;
    Tile_hero_controlled_by = Hero();
    Tile_has_dragonglass = false;
    Tile_has_wildfire = false;
} //default constructor

Tile::Tile(int typePC, char letterPC, string namePC, int moneyPC, int army_sizePC, int pointsPC, Hero hero_controlled_byPC, bool has_dragonglassPC, bool has_wildfirePC) {
    if(typePC >= 1 && typePC <= 3)
    {
        Tile_type = typePC;
    }
    else
    {
        Tile_type = 0;
    }
    Tile_letter = letterPC;
    Tile_name = namePC;
    Tile_money = moneyPC;
    Tile_army_size = army_sizePC;
    Tile_points = pointsPC;
    Tile_hero_controlled_by = hero_controlled_byPC;
    Tile_has_dragonglass = has_dragonglassPC;
    Tile_has_wildfire = has_wildfirePC;
}

void Tile::Tile_setType(int typeInput) {
    if(typeInput >= 1 && typeInput <= 3)
    {
        Tile_type = typeInput;
    }
    else
    {
        Tile_type = 0;
    }
} //set tile type

int Tile::Tile_getType() {
    return Tile_type;
} //return tile type

void Tile::Tile_setLetter(char letterInput) {
    Tile_letter = letterInput;
} //set tile letter

char Tile::Tile_getLetter() {
    return Tile_letter;
} //return tile letter

void Tile::Tile_setName(string nameInput) {
    Tile_name = nameInput;
} //set tile name

string Tile::Tile_getName() {
    return Tile_name;
} //return tile name

void Tile::Tile_setMoney(int moneyInput) {
    Tile_money = moneyInput;
} //set tile money

int Tile::Tile_getMoney() {
    return Tile_money;
} //return tile money

void Tile::Tile_setArmy_Size(int army_sizeInput) {
    Tile_army_size = army_sizeInput;
} //set tile army size

int Tile::Tile_getArmy_Size() {
    return Tile_army_size;
} //return tile army size

void Tile::Tile_setPoints(int pointsInput) {
    Tile_points = pointsInput;
} //set tile points

int Tile::Tile_getPoints() {
    return Tile_points;
} //return tile points

void Tile::Tile_set_hero_controlled_by(Hero hero_controlled_byInput){
    Tile_hero_controlled_by = hero_controlled_byInput;
} //set tile hero controlled by

Hero Tile::Tile_get_hero_controlled_by() {
    return Tile_hero_controlled_by;
} //return tile hero controlled by

void Tile::Tile_set_has_dragonglass(bool dragonglassInput) {
    Tile_has_dragonglass = dragonglassInput;
} //set if tile has dragonglass

bool Tile::Tile_get_has_dragonglass() {
    return Tile_has_dragonglass;
} //return if tile has dragonglass

void Tile::Tile_set_has_wildfire(bool wildfireInput) {
    Tile_has_wildfire = wildfireInput;
} //set if tile has wildfire

bool Tile::Tile_get_has_wildfire() {
    return Tile_has_wildfire;
} //return if tile hs wildfire
