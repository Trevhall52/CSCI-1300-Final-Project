#include <cstdlib>
#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int split(string str, char delimiter, string arr[], int max) //split function
{
    int a = 0; // value of array
    if (str.length() == 0) //If there is no string, value = 0
    {
        return 0;
    }
    string word = "";//empty string
    str = str + delimiter;
        for (int i = 0; i < str.length(); i++) //traverse
        {
            if (str[i] == delimiter) //when it reaches delimiter
            {
                if (word.length() == 0) continue;
                arr[a] = word; //populate array
                a++; // array placement increases
                word = ""; //start word over
            }
            else
            {
                word = word + str[i]; //populate string
            }
        }
        return 0;
}

Map::Map() {
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            map[i][j] = Tile();
        }
    }
} //default constructor

int Map::Map_setMap(string FileName) {
    ifstream in_file;
    in_file.open(FileName);
    if(in_file.fail()) //if it fails to open
    {
        return -1;
    }
    else
    {
        int row = 0;
        string line = ""; //blank string for populating
        while(getline(in_file,line))
        {
            string temp[16]; //temporary array
            split(line, ',', temp, 16);
            for(int i = 0; i < 16; i++)
            {
                if(temp[i] == "p")
                {
                    map[row][i].Tile_setType(2);
                    map[row][i].Tile_setLetter(' ');
                }
                else if(temp[i] == "w")
                {
                    map[row][i].Tile_setType(1);
                    map[row][i].Tile_setLetter(' ');
                }
                else
                {
                    map[row][i].Tile_setType(3);
                    map[row][i].Tile_setLetter(temp[i][0]);
                }
            }
            row++;
        }
    }
} //read filename, set map

void Map::Map_testCoutWholeMap() {
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            if(map[i][j].Tile_getType() == 1)
            {
                cout << "~";
                cout << " ";
            }
            else if(map[i][j].Tile_getType() == 2)
            {
                cout << "_";
                cout << " ";
            }
            else
            {
                cout << map[i][j].Tile_getLetter();
                cout << " ";
            }
        }
        cout << endl;
    }
} //print entire map (for testing purposes)

void Map::Map_minimap(Hero heroInput) {
    cout << endl;
    for(int j = -3; j < 4; j++)
    {
        for(int i = -3; i < 4; i++)
        {
            if(heroInput.Hero_getLocation_Row() + j < 0 || heroInput.Hero_getLocation_Column() + i < 0 || heroInput.Hero_getLocation_Row() + j > 24 || heroInput.Hero_getLocation_Column() + i > 15)
                {
                    cout << "X";
                    cout << " ";
                }
            else if((map[heroInput.Hero_getLocation_Row() + j][heroInput.Hero_getLocation_Column() + i].Tile_getType()) == 1)
            {
                if(heroInput.Hero_getLocation_Row() + j < 0 || heroInput.Hero_getLocation_Column() + i < 0 || heroInput.Hero_getLocation_Row() + j > 24 || heroInput.Hero_getLocation_Column() + i > 15)
                {
                    cout << "X";
                    cout << " ";
                }
                else if((heroInput.Hero_getLocation_Column() + i) == heroInput.Hero_getLocation_Column() && (heroInput.Hero_getLocation_Row() + j) == heroInput.Hero_getLocation_Row())
                {
                    cout << "+";
                    cout << " ";
                }
                else
                {
                    cout << "~";
                    cout << " ";
                }
            }
            else if((map[heroInput.Hero_getLocation_Row() + j][heroInput.Hero_getLocation_Column() + i].Tile_getType()) == 2)
            {
                if(heroInput.Hero_getLocation_Row() + j < 0 || heroInput.Hero_getLocation_Column() + i < 0 || heroInput.Hero_getLocation_Row() + j > 24 || heroInput.Hero_getLocation_Column() + i > 15)
                {
                    cout << "X";
                    cout << " ";
                }
                else if((heroInput.Hero_getLocation_Column() + i) == heroInput.Hero_getLocation_Column() && (heroInput.Hero_getLocation_Row() + j) == heroInput.Hero_getLocation_Row())
                {
                    cout << "+";
                    cout << " ";
                }
                else
                {
                    cout << "_";
                    cout << " ";
                }
            }
            else
            {
                if(heroInput.Hero_getLocation_Row() + j < 0 || heroInput.Hero_getLocation_Column() + i < 0 || heroInput.Hero_getLocation_Row() + j > 24 || heroInput.Hero_getLocation_Column() + i > 15)
                {
                    cout << "X";
                    cout << " ";
                }
                else if((heroInput.Hero_getLocation_Column() + i) == heroInput.Hero_getLocation_Column() && (heroInput.Hero_getLocation_Row() + j) == heroInput.Hero_getLocation_Row())
                {
                    cout << "+";
                    cout << " ";
                }
                else
                {
                    cout << map[heroInput.Hero_getLocation_Row() + j][heroInput.Hero_getLocation_Column() + i].Tile_getLetter();
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
} //minimap function

Tile Map::Map_getTile(int rowInput, int columnInput) {
    return map[rowInput][columnInput];
} //return specific tile

void Map::Map_setTileName(int rowInput, int columnInput, string nameInput) {
    map[rowInput][columnInput].Tile_setName(nameInput);
} //set specific tile name

void Map::Map_setTileMoney(int rowInput, int columnInput, int moneyInput) {
    map[rowInput][columnInput].Tile_setMoney(moneyInput);
} //set specific tile money

void Map::Map_setTileArmySize(int rowInput, int columnInput, int armySizeInput) {
    map[rowInput][columnInput].Tile_setArmy_Size(armySizeInput);
} //set tile army size

void Map::Map_setTilePoints(int rowInput, int columnInput, int pointsInput) {
    map[rowInput][columnInput].Tile_setPoints(pointsInput);
} //set tile points

void Map::Map_setHeroControlledBy(int rowInput, int columnInput, Hero heroControlledByInput) {
    map[rowInput][columnInput].Tile_set_hero_controlled_by(heroControlledByInput);
} //set tile hero controlled by

void Map::Map_setDragonglass(int rowInput, int columnInput, bool dragonglassInput) {
    map[rowInput][columnInput].Tile_set_has_dragonglass(dragonglassInput);
} //set if tile has dragonglass

void Map::Map_setWildfire(int rowInput, int columnInput, bool wildfireInput) {
    map[rowInput][columnInput].Tile_set_has_wildfire(wildfireInput);
} //set if tile has wildfire
