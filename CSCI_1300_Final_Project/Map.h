#ifndef MAP_H
#define MAP_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Warrior.h"
#include "Hero.h"
#include "Tile.h"

using namespace std;

class Map
{
public:
    Map();
    int Map_setMap(string FileName);
    void Map_testCoutWholeMap();
    void Map_minimap(Hero heroInput);
    Tile Map_getTile(int rowInput, int columnInput);
    void Map_setTileName(int rowInput, int columnInput, string nameInput);
    void Map_setTileMoney(int rowInput, int columnInput, int moneyInput);
    void Map_setTileArmySize(int rowInput, int columnInput, int armySizeInput);
    void Map_setTilePoints(int rowInput, int columnInput, int pointsInput);
    void Map_setHeroControlledBy(int rowInput, int columnInput, Hero heroControlledByInput);
    void Map_setDragonglass(int rowInput, int columnInput, bool dragonglassInput);
    void Map_setWildfire(int rowInput, int columnInput, bool wild);
private:
    Tile map[25][16];
};

#endif
