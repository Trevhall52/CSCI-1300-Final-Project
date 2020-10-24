#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cmath>
#include <random>
#include <unistd.h>
#include <stdio.h>
#include "Warrior.cpp"
#include "Hero.cpp"
#include "Tile.cpp"
#include "Map.cpp"
#include "Game.cpp"

using namespace std;

void game()
{
    srand (0); //initialize random
    Game G1;
    int turns = 0;
    G1.Game_warrior_initialization("warriors.txt"); //initialize warriors
    G1.Game_hero_initialization("heroes.txt"); //initialize heroes
    G1.Game_setNumHeroes(); //establish number of heroes
    Map M1;
    M1.Map_setMap("map.txt");
    G1.Game_setMap(M1); //set map
    G1.Game_city_initialization("cities.txt"); //set cities
    G1.Game_setWarriorLocations(); //set warrior locations
    G1.Game_scatter_dragonglass(); //scatter dragonglass
    G1.Game_logo(); //display logo
    G1.Game_introduction(); //introduce game
    G1.Game_setNumHeroes(); //change number of heroes
    G1.Game_firstTurnSequence(); //sequence of first turn
    for(int i = 0; i < 100; i++)
    {
        G1.Game_gameTurnLoop(); //turn loop
        if(G1.Game_getTurns() == 10)
        {
            G1.Game_preset_ten_turns(); //ten turn presets
        }
        if(G1.Game_getTurns() >= 12 || G1.Game_get_hero_controlled_by_player().Hero_getArmySize() > 2000 || G1.Game_get_hero_controlled_by_player().Hero_getScore() > 400 || G1.Game_getNumDeadHeroes() == G1.Game_getNumHeroes()-1 || G1.Game_getTilesControlled(G1.Game_returnHero_controlled_by_playerindex()) == 200)
        {
            G1.Game_is_winter_coming(); //initialize white walker battle
        }
        if(G1.Game_get_hero_controlled_by_player().Hero_get_death() == true)
        {
            G1.Game_gameDeath(); //death sequence
            G1.Game_scoreDisplay(); //display score
            return;
        }
        if(G1.Game_get_is_victorious() == true)
        {
            G1.Game_winnerDisplay(); //winner display
            G1.Game_logo(); //logo
            G1.Game_scoreDisplay(); //display score
            return;
        }
        turns++;
    }
}

int main()
{
    game();
}
