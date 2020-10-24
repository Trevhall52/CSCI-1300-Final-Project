#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Hero.h"

using namespace std;

class Tile
{
public:
    Tile();
    Tile(int typePC, char letterPC, string namePC, int moneyPC, int army_sizePC, int pointsPC, Hero hero_controlled_byPC, bool has_dragonglassPC, bool has_wildfirePC);
    void Tile_setType(int typeInput);
    int Tile_getType();
    void Tile_setLetter(char letterInput);
    char Tile_getLetter();
    void Tile_setName(string nameInput);
    string Tile_getName();
    void Tile_setMoney(int moneyInput);
    int Tile_getMoney();
    void Tile_setArmy_Size(int army_sizeInput);
    int Tile_getArmy_Size();
    void Tile_setPoints(int pointsInput);
    int Tile_getPoints();
    void Tile_set_hero_controlled_by(Hero hero_controlled_byInput);
    Hero Tile_get_hero_controlled_by();
    void Tile_set_has_dragonglass(bool dragonglassInput);
    bool Tile_get_has_dragonglass();
    void Tile_set_has_wildfire(bool wildfireInput);
    bool Tile_get_has_wildfire();
private:
    int Tile_type; //1=water,2=land,3=city
    char Tile_letter;
    string Tile_name; //default to "" if water or land
    int Tile_money;
    int Tile_army_size;
    int Tile_points;
    Hero Tile_hero_controlled_by;
    bool Tile_has_dragonglass;
    bool Tile_has_wildfire;
};

#endif
