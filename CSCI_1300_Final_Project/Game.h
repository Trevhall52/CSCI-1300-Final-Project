#ifndef GAME_H
#define GAME_H

#include <string>
#include <random>
#include <cstdlib>
#include "Warrior.h"
#include "Hero.h"
#include "Tile.h"
#include "Map.h"

class Game
{
private :
    Map Game_map;
    vector <Hero> heroes;
    vector <Warrior> warriors;
    int numHeroes;
    int numDeadHeroes;
    int turns;
    string playerName;
    int whiteWalkerPasses = 0;
    bool victorious;
public:
    Game();
    Warrior Game_getWarrior(int addressInput); //
    Hero Game_getHero(int addressInput); //
    void Game_setMap(Map map);
    Map Game_getMap();
    int Game_getNumHeroes(); //
    int Game_getNumDeadHeroes(); //
    int Game_getNumWarriors(); //
    void Game_setTurns(int turnsInput); //
    void Game_setNumHeroes(); //
    int Game_getTurns(); //
    void Game_logo(); //
    void Game_introduction();
    void Game_hero_initialization(string fileName); //
    void Game_warrior_initialization(string fileName); //
    void Game_city_initialization(string filename); //
    void Game_scatter_dragonglass();
    void Game_setPlayerName(string playerNameInput); //
    string Game_getPlayerName(); //
    Hero Game_get_hero_controlled_by_player(); //
    void Game_set_tile_control(int rowInput, int columnInput, Hero hero); //
    void Game_firstTurnSequence(); //
    void Game_gameTurnLoop();
    bool Game_is_in_vicinity_hero(Hero heroInput); //
    Hero Game_getNearesthero(Hero heroInput); //
    int Game_getNearestWarrior(Hero heroInput); //
    bool Game_is_in_vicinity_warrior(Hero heroInput);
    bool Game_warriors_have_ship(Hero hero);
    bool Game_playerCanMoveInDirection(int directionInput); //
    bool Game_heroCanMoveInDirection(int i, int directionInput); //
    int Game_returnHero_controlled_by_playerindex(); //
    void Game_movePlayer(int indexInput, int directionInput); //
    void Game_resolvePlayerEncounter();
    int Game_randomInteger(); //
    void Game_setInfluence(int indexInput, int influenceInput); //
    void Game_setMoney(int indexInput, int moneyInput); //
    void Game_setArmySize(int indexInput, int armySizeInput); //
    void Game_setPoints(int indexInput, int pointsInput); //
    void Game_set_is_dead(int indexInput, bool deathInput); //
    int Game_returnHeroIndex(Hero hero); //
    void Game_setWarriors(int indexInput, int warriorIndexInput, Warrior warrior); //
    bool Game_hasWildfire(Hero hero); //
    void Game_gameDeath(); //
    void Game_updatePoints(int index); //
    void Game_checkTile(int rowInput, int columnInput); //
    void Game_preset_ten_turns(); //
    void Game_has_arrived_in_city();
    Hero Game_find_nearest_hero();
    void Game_is_winter_coming();
    void Game_whiteWalkerBattle();
    int Game_getCitiesControlled(int index); //
    void Game_is_victorious();
    void Game_winnerDisplay();
    bool Game_get_is_victorious();
    void Game_scoreDisplay();
    void Game_randomEvents();
    int Game_getTilesControlled(int index);
    void Game_moveOtherHeroes();
    void Game_setWarriorLocations();
    void Game_acquireWarriors();
    void Game_resolveCPUEncounters();

};

#endif
