#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cmath>
#include <unistd.h>
#include <stdio.h>
#include <random>
#include "Warrior.h"
#include "Hero.h"
#include "Tile.h"
#include "Map.h"
#include "Game.h"

using namespace std;

Game::Game() {
    vector <Hero> blankH;
    vector <Warrior> blankW;
    heroes = blankH;
    warriors = blankW;
    numHeroes = 0;
    numDeadHeroes = 0;
    turns = 0;
    victorious = false;
} //default constructor

Warrior Game::Game_getWarrior(int addressInput) {
    return warriors[addressInput];
} //return warrior at address

Hero Game::Game_getHero(int addressInput) {
    return heroes[addressInput];
} //return hero at address

void Game::Game_setMap(Map map) {
    Game_map = map;
} //set map

Map Game::Game_getMap() {
    return Game_map;
} //return entire map

int Game::Game_getNumHeroes() {
    return numHeroes;
} //get number of heroes

int Game::Game_getNumDeadHeroes() {
    return numDeadHeroes;
} //get number of dead heroes

int Game::Game_getNumWarriors() {
    return warriors.size();
} //get number of warriors

void Game::Game_setTurns(int turnsInput) {
    turns = turnsInput;
} //set number of turns

void Game::Game_setNumHeroes() {
    numHeroes = heroes.size();
} //set number of heroes

int Game::Game_getTurns() {
    return turns;
} //get number of turns

void Game::Game_setPlayerName(string playerNameInput) {
    playerName = playerNameInput;
} //set player name to string

string Game::Game_getPlayerName() {
    return playerName;
} //return player name

void Game::Game_logo() {
    cout << "   _____                               __   _______ _                               |`-._()_.-`|" << endl;
    cout << "  / ____|                             / _| |__   __| |                              |    ||    |" << endl;
    cout << " | |  __  __ _ _ __ ____   ___    ___| |_     | |  | |__  _ __ ___  _ ___  ___  ___ |    ||    |" << endl;
    cout << " | | |_ |/ _` | '_ ` _  | / _ | / _ ||  _|    | |  | '_  | '__/ _ || '_  |/ _ |/ __||__((<>))__|" << endl;
    cout << " | |__| ||(_| | | | | | || __/  |(_)|| |      | |  | | | | |  |(_)|| | | || __/|__ ||   o()o   |" << endl;
    cout << "  |_____||__,_|_| |_| |_||___|  |___/|_/      |_|  |_| |_|_|  |___/|_| |_||___||___/|    ||    |" << endl;
    cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  '.  ||  .' " << endl;
    cout << "Trevor Hall - CSCI 1300                                                                '.||.'   " << endl;
} //print ascii logo

/*recieve filename
split file statistics
create new hero with name, statistics, etc.
implement hero into heroes vector
*/
void Game::Game_hero_initialization(string fileName) {
    ifstream in_file;
    in_file.open(fileName);
    if(in_file.fail()) //if it fails to open
    {
        return;
    }
    else
    {
        string line = ""; //blank string for populating
        while(getline(in_file,line))
        {
            int address = 0;
            string temp[16]; //temporary array
            split(line, ',', temp, 16);
            Hero H1; //create temporary hero
            H1.Hero_setName(temp[0]);
            H1.Hero_setMoney(stoi(temp[1]));
            H1.Hero_setInfluence(stoi(temp[2]));
            H1.Hero_setArmySize(stoi(temp[3]));
            for(int i = 4; i < 8; i++)
            {
                for(int j = 0; j < warriors.size(); j++)
                {
                    if(warriors[j].Warrior_getName() == temp[i])
                    {
                        H1.Hero_setWarriors(warriors[j], address); //set warrior
                        address++;
                    }
                }
            }
            H1.Hero_setLocation_Row(stoi(temp[8]));
            H1.Hero_setLocation_Column(stoi(temp[9]));
            if(temp[10] == "yes")
            {
                H1.Hero_set_has_Ship(1);
            }
            else if(temp[10] == "no")
            {
                H1.Hero_set_has_Ship(0);
            }
            heroes.push_back(H1); //add hero to array
        }
    }
} //initialize heroes from file

/*recieve filename
split file statistics
create new warrior with name, statistics, etc.
implement warrior into warriors vector
*/
void Game::Game_warrior_initialization(string fileName) {
    ifstream in_file;
    in_file.open(fileName);
    if(in_file.fail()) //if it fails to open
    {
        return;
    }
    else
    {
        string line = ""; //blank string for populating
        while(getline(in_file,line))
        {
            string temp[16]; //temporary array
            split(line, ',', temp, 16);
            Warrior W1;
            W1.Warrior_setName(temp[0]);
            W1.Warrior_setStrength(stoi(temp[1]));
            W1.Warrior_setLoyalty(stoi(temp[2]));
            W1.Warrior_setMorale(stoi(temp[3]));
            if(temp[4] == "yes")
            {
                W1.Warrior_set_is_free(1);
            }
            else if(temp[4] == "no")
            {
                W1.Warrior_set_is_free(0);
            }
            if(temp[5] == "yes")
            {
                W1.Warrior_set_has_ship(1);
            }
            else if(temp[5] == "no")
            {
                W1.Warrior_set_has_ship(0);
            }
            if(temp[6] == "yes")
            {
                W1.Warrior_set_has_wildfire(1);
            }
            else if(temp[6] == "no")
            {
                W1.Warrior_set_has_wildfire(0);
            }
            if(temp[7] == "yes")
            {
                W1.Warrior_set_has_dragonglass(1);
            }
            else if(temp[7] == "no")
            {
                W1.Warrior_set_has_dragonglass(0);
            }
            warriors.push_back(W1); //add warrior to vector
        }
    }
} //initialize warriors from file

/*recieve filename
split file statistics
create new city with name, statistics, etc.
match tile letter with city letter
when finds match, implement statistics to that specific tile
*/
void Game::Game_city_initialization(string fileName) {
    ifstream in_file;
    in_file.open(fileName);
    if(in_file.fail()) //if it fails to open
    {
        return;
    }
    else
    {
        string line = ""; //blank string for populating
        while(getline(in_file,line))
        {
            string temp[6]; //temporary array
            split(line, ',', temp, 16);
            for(int i = 0; i < 25; i++) //for each tile
            {
                for(int j = 0; j < 16; j++)
                {
                    if(Game_map.Map_getTile(i,j).Tile_getLetter() == temp[0][0])
                    {
                        Game_map.Map_setTileName(i,j,temp[1]);
                        Game_map.Map_setTileMoney(i,j,stoi(temp[2]));
                        Game_map.Map_setTileArmySize(i,j,stoi(temp[3]));
                        Game_map.Map_setTilePoints(i,j,stoi(temp[4]));
                        if(temp[5] == "0")
                        {
                            Game_map.Map_setWildfire(i,j,false);
                        }
                        else if(temp[5] == "1")
                        {
                            Game_map.Map_setWildfire(i,j,true);
                        }

                    }
                }
            }
        }
    }
} //initialize cities from file

/*Beginning of the game!!
choosing hero/creation of hero
recieving statistics for create hero, otherwise set chosen hero as controlled
accounts for user error!
*/
void Game::Game_introduction() {
    string playerNameA;
    string playerChoiceHero;
    cout << endl;
    cout << "State your name, your grace: " << endl; //recieve player name
    cin >> playerNameA;
    Game_setPlayerName(playerNameA);
    cout << endl;
    cout << "Would you like to choose a hero, " << Game_getPlayerName() <<"? (Y/N)";
    cin >> playerChoiceHero;
    if(playerChoiceHero != "Y" && playerChoiceHero != "y" && playerChoiceHero != "N" && playerChoiceHero != "n")
    {
        while(playerChoiceHero != "Y" && playerChoiceHero != "y" && playerChoiceHero != "N" && playerChoiceHero != "n") //prevent user error
        {
            cout << "Good one. Do you want to choose a hero or not?";
            cin >> playerChoiceHero;
        }
    }
    if(playerChoiceHero == "Y" || playerChoiceHero == "y")
    {
        string heroChoice;
        cout << endl;
        cout << "Please choose from the following heroes:" << endl; //display all heroes
        cout << endl;
        cout << "1. " << Game_getHero(0).Hero_getName() << endl;
        cout << "2. " << Game_getHero(1).Hero_getName() << endl;
        cout << "3. " << Game_getHero(2).Hero_getName() << endl;
        cout << "4. " << Game_getHero(3).Hero_getName() << endl;
        cout << "5. " << Game_getHero(4).Hero_getName() << endl;
        cout << "6. " << Game_getHero(5).Hero_getName() << endl;
        cin >> heroChoice;
        while(heroChoice != "1" && heroChoice != "2" && heroChoice != "3" && heroChoice != "4" && heroChoice != "5" && heroChoice != "6") //prevent user error
        {
            cout << "Please choose a hero (1-6)." << endl;
            cin >> heroChoice;
        }
        heroes[stoi(heroChoice) - 1].Hero_set_is_controlled_by_player(true); //set player controlled
    }
    if(playerChoiceHero == "N" || playerChoiceHero == "n") //create a hero intitialization
    {
        cout << endl;
        cout << "Your Grace " << Game_getPlayerName() << ", you have chosen to go on this journey alone." << endl;
        cout << "Please provide starting values for your adventure.";
        string moneyPlayerInput;
        string influencePlayerInput;
        string armySizePlayerInput;
        string rowLocationPlayerInput;
        string columnLocationPlayerInput;
        string shipPlayerInput;
        cout << endl;
        cout << endl;
        cout << "How much money will you start with? (0-10000)";
        cin >> moneyPlayerInput;
        for(int i = 0; i < moneyPlayerInput.length(); i++)
        {
           if(moneyPlayerInput[i] != '0' && moneyPlayerInput[i] != '1' && moneyPlayerInput[i] != '2' && moneyPlayerInput[i] != '3' && moneyPlayerInput[i] != '4' && moneyPlayerInput[i] != '5' && moneyPlayerInput[i] != '6' && moneyPlayerInput[i] != '7' && moneyPlayerInput[i] != '8' && moneyPlayerInput[i] != '9')
           {
               moneyPlayerInput = "10001";
           }
        }
        while(stoi(moneyPlayerInput) > 10000 || stoi(moneyPlayerInput) < 0) //prevent user error
        {
            cout << "The bank can only do so much." << endl;
            cout << "How much money will you start with? (0-10000)";
            cin >> moneyPlayerInput;
            for(int i = 0; i < moneyPlayerInput.length(); i++)
            {
               if(moneyPlayerInput[i] != '0' && moneyPlayerInput[i] != '1' && moneyPlayerInput[i] != '2' && moneyPlayerInput[i] != '3' && moneyPlayerInput[i] != '4' && moneyPlayerInput[i] != '5' && moneyPlayerInput[i] != '6' && moneyPlayerInput[i] != '7' && moneyPlayerInput[i] != '8' && moneyPlayerInput[i] != '9')
               {
                   moneyPlayerInput = "10001"; //if incorrect input
               }
            }
        }
        cout << endl;
        cout << "How strong is your influence? (0-500) ";
        cin >> influencePlayerInput;
        for(int i = 0; i < influencePlayerInput.length(); i++)
        {
           if(influencePlayerInput[i] != '0' && influencePlayerInput[i] != '1' && influencePlayerInput[i] != '2' && influencePlayerInput[i] != '3' && influencePlayerInput[i] != '4' && influencePlayerInput[i] != '5' && influencePlayerInput[i] != '6' && influencePlayerInput[i] != '7' && influencePlayerInput[i] != '8' && influencePlayerInput[i] != '9')
           {
               influencePlayerInput = "501"; //if incorrect input
           }
        }
        while(stoi(influencePlayerInput) > 500 ||stoi(influencePlayerInput) < 0) //prevent user error
        {
            cout << "Let's not kid ourselves." << endl;
            cout << "How strong is your influence? (0-500) ";
            cin >> influencePlayerInput;
            for(int i = 0; i < influencePlayerInput.length(); i++)
            {
               if(influencePlayerInput[i] != '0' && influencePlayerInput[i] != '1' && influencePlayerInput[i] != '2' && influencePlayerInput[i] != '3' && influencePlayerInput[i] != '4' && influencePlayerInput[i] != '5' && influencePlayerInput[i] != '6' && influencePlayerInput[i] != '7' && influencePlayerInput[i] != '8' && influencePlayerInput[i] != '9')
               {
                   influencePlayerInput = "501"; //if incorrect input
               }
            }
        }
        cout << endl;
        cout << "How large is your army? (0-1000)";
        cin >> armySizePlayerInput;
        for(int i = 0; i < armySizePlayerInput.length(); i++)
        {
           if(armySizePlayerInput[i] != '0' && armySizePlayerInput[i] != '1' && armySizePlayerInput[i] != '2' && armySizePlayerInput[i] != '3' && armySizePlayerInput[i] != '4' && armySizePlayerInput[i] != '5' && armySizePlayerInput[i] != '6' && armySizePlayerInput[i] != '7' && armySizePlayerInput[i] != '8' && armySizePlayerInput[i] != '9')
           {
               armySizePlayerInput = "1001";
           }
        }
        while(stoi(armySizePlayerInput) > 1000 || stoi(armySizePlayerInput) < 0) //prevent user error
        {
            cout << "Listen to the instructions, dude." << endl;
            cout << "How large is your army? (0-1000)";
            cin >> armySizePlayerInput;
            for(int i = 0; i < armySizePlayerInput.length(); i++)
            {
               if(armySizePlayerInput[i] != '0' && armySizePlayerInput[i] != '1' && armySizePlayerInput[i] != '2' && armySizePlayerInput[i] != '3' && armySizePlayerInput[i] != '4' && armySizePlayerInput[i] != '5' && armySizePlayerInput[i] != '6' && armySizePlayerInput[i] != '7' && armySizePlayerInput[i] != '8' && armySizePlayerInput[i] != '9')
               {
                   armySizePlayerInput = "1001"; //if incorrect input
               }
            }
        }
        cout << endl;
        cout << "What row will you start on? (0-24) ";
        cin >> rowLocationPlayerInput;
        for(int i = 0; i < rowLocationPlayerInput.length(); i++)
        {
           if(rowLocationPlayerInput[i] != '0' && rowLocationPlayerInput[i] != '1' && rowLocationPlayerInput[i] != '2' && rowLocationPlayerInput[i] != '3' && rowLocationPlayerInput[i] != '4' && rowLocationPlayerInput[i] != '5' && rowLocationPlayerInput[i] != '6' && rowLocationPlayerInput[i] != '7' && rowLocationPlayerInput[i] != '8' && rowLocationPlayerInput[i] != '9')
           {
               rowLocationPlayerInput = "25"; //if incorrect input
           }
        }
        while(stoi(rowLocationPlayerInput) > 24 || stoi(rowLocationPlayerInput) < 0) //in case of user error
        {
            cout << "You cannot begin outside of the wall." << endl;
            cout << "What row will you start on? (0-24) ";
            cin >> rowLocationPlayerInput;
            for(int i = 0; i < rowLocationPlayerInput.length(); i++)
            {
               if(rowLocationPlayerInput[i] != '0' && rowLocationPlayerInput[i] != '1' && rowLocationPlayerInput[i] != '2' && rowLocationPlayerInput[i] != '3' && rowLocationPlayerInput[i] != '4' && rowLocationPlayerInput[i] != '5' && rowLocationPlayerInput[i] != '6' && rowLocationPlayerInput[i] != '7' && rowLocationPlayerInput[i] != '8' && rowLocationPlayerInput[i] != '9')
               {
                   rowLocationPlayerInput = "25"; //if incorrect input
               }
            }
        }
        cout << endl;
        cout << "What column will you start on? (0-15) ";
        cin >> columnLocationPlayerInput;
        for(int i = 0; i < columnLocationPlayerInput.length(); i++)
        {
           if(columnLocationPlayerInput[i] != '0' && columnLocationPlayerInput[i] != '1' && columnLocationPlayerInput[i] != '2' && columnLocationPlayerInput[i] != '3' && columnLocationPlayerInput[i] != '4' && columnLocationPlayerInput[i] != '5' && columnLocationPlayerInput[i] != '6' && columnLocationPlayerInput[i] != '7' && columnLocationPlayerInput[i] != '8' && columnLocationPlayerInput[i] != '9')
           {
               columnLocationPlayerInput = "16";
           }
        }
        while(stoi(columnLocationPlayerInput) > 15 || stoi(columnLocationPlayerInput) < 0) //preventing user error
        {
            cout << "You cannot begin outside of the wall." << endl;
            cout << "What column will you start on? (0-15) ";
            cin >> columnLocationPlayerInput;
            for(int i = 0; i < columnLocationPlayerInput.length(); i++)
            {
               if(columnLocationPlayerInput[i] != '0' && columnLocationPlayerInput[i] != '1' && columnLocationPlayerInput[i] != '2' && columnLocationPlayerInput[i] != '3' && columnLocationPlayerInput[i] != '4' && columnLocationPlayerInput[i] != '5' && columnLocationPlayerInput[i] != '6' && columnLocationPlayerInput[i] != '7' && columnLocationPlayerInput[i] != '8' && columnLocationPlayerInput[i] != '9')
               {
                   columnLocationPlayerInput = "16"; //if incorrect input
               }
            }
        }
        for(int i = 0; i < Game_getNumHeroes(); i++)
        {
            while(stoi(columnLocationPlayerInput) == heroes[i].Hero_getLocation_Column() && stoi(rowLocationPlayerInput) == heroes[i].Hero_getLocation_Row()) //checking if location is same as other hero
            {
                cout << "You cannot start in the same location as another Hero." << endl;
                cout << "Please choose a new Location." << endl;
                cout << "Row: ";
                cin >> rowLocationPlayerInput;
                cout << endl;
                cout << "Column: ";
                cin >> columnLocationPlayerInput;
                i = 0;
                for(int i = 0; i < rowLocationPlayerInput.length(); i++)
                {
                   if(rowLocationPlayerInput[i] != '0' && rowLocationPlayerInput[i] != '1' && rowLocationPlayerInput[i] != '2' && rowLocationPlayerInput[i] != '3' && rowLocationPlayerInput[i] != '4' && rowLocationPlayerInput[i] != '5' && rowLocationPlayerInput[i] != '6' && rowLocationPlayerInput[i] != '7' && rowLocationPlayerInput[i] != '8' && rowLocationPlayerInput[i] != '9')
                   {
                       rowLocationPlayerInput = "25"; //if incorrect input
                   }
                }
                while(stoi(rowLocationPlayerInput) > 24 || stoi(rowLocationPlayerInput) < 0)
                {
                    cout << "You cannot begin outside of the wall." << endl;
                    cout << "What row will you start on? (0-24) ";
                    cin >> rowLocationPlayerInput;
                    for(int i = 0; i < rowLocationPlayerInput.length(); i++)
                    {
                       if(rowLocationPlayerInput[i] != '0' && rowLocationPlayerInput[i] != '1' && rowLocationPlayerInput[i] != '2' && rowLocationPlayerInput[i] != '3' && rowLocationPlayerInput[i] != '4' && rowLocationPlayerInput[i] != '5' && rowLocationPlayerInput[i] != '6' && rowLocationPlayerInput[i] != '7' && rowLocationPlayerInput[i] != '8' && rowLocationPlayerInput[i] != '9')
                       {
                           rowLocationPlayerInput = "25"; //if incorrect input
                       }
                    }
                }
                for(int i = 0; i < columnLocationPlayerInput.length(); i++)
                {
                   if(columnLocationPlayerInput[i] != '0' && columnLocationPlayerInput[i] != '1' && columnLocationPlayerInput[i] != '2' && columnLocationPlayerInput[i] != '3' && columnLocationPlayerInput[i] != '4' && columnLocationPlayerInput[i] != '5' && columnLocationPlayerInput[i] != '6' && columnLocationPlayerInput[i] != '7' && columnLocationPlayerInput[i] != '8' && columnLocationPlayerInput[i] != '9')
                   {
                       columnLocationPlayerInput = "16"; //if incorrect input
                   }
                }
                while(stoi(columnLocationPlayerInput) > 15 || stoi(columnLocationPlayerInput) < 0)
                {
                    cout << "You cannot begin outside of the wall." << endl;
                    cout << "What column will you start on? (0-15) ";
                    cin >> columnLocationPlayerInput;
                    for(int i = 0; i < columnLocationPlayerInput.length(); i++)
                    {
                       if(columnLocationPlayerInput[i] != '0' && columnLocationPlayerInput[i] != '1' && columnLocationPlayerInput[i] != '2' && columnLocationPlayerInput[i] != '3' && columnLocationPlayerInput[i] != '4' && columnLocationPlayerInput[i] != '5' && columnLocationPlayerInput[i] != '6' && columnLocationPlayerInput[i] != '7' && columnLocationPlayerInput[i] != '8' && columnLocationPlayerInput[i] != '9')
                       {
                           columnLocationPlayerInput = "16"; //if incorrect input
                       }
                    }
                }
            }
        }
        cout << endl;
        if(Game_getMap().Map_getTile(stoi(rowLocationPlayerInput), stoi(columnLocationPlayerInput)).Tile_getType() != 1)
        {
            cout << "Will you start with a ship? (Y/N) ";
            cin >> shipPlayerInput;
            while(shipPlayerInput != "Y" && shipPlayerInput != "y" && shipPlayerInput != "N" && shipPlayerInput != "n") //user error
            {
                cout << "English, not Valerian" << endl;
                cout << "Will you start with a ship? (Y/N) ";
                cin >> shipPlayerInput;
            }
            cout << endl;
        }
        else
        {
            shipPlayerInput = "Y";
        }
        Hero H1; //hero creation based on input
        H1.Hero_setName(Game_getPlayerName());
        H1.Hero_setMoney(stoi(moneyPlayerInput));
        H1.Hero_setInfluence(stoi(influencePlayerInput));
        H1.Hero_setArmySize(stoi(armySizePlayerInput));
        H1.Hero_setLocation_Row(stoi(rowLocationPlayerInput));
        H1.Hero_setLocation_Column(stoi(columnLocationPlayerInput));
        if(shipPlayerInput == "Y" || shipPlayerInput == "y")
        {
            H1.Hero_set_has_Ship(true);
        }
        else
        {
            H1.Hero_set_has_Ship(false);
        }
        H1.Hero_set_is_controlled_by_player(true);
        heroes.push_back(H1); //add to vector
    }
} //introduction sequence (character selection / creation)

Hero Game::Game_get_hero_controlled_by_player() {
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        if(heroes[i].Hero_get_is_controlled_by_player() == true)
        {
            return heroes[i];
        }
    }
} //return hero controlled by player

void Game::Game_set_tile_control(int row, int column, Hero hero) {
    Game_map.Map_setHeroControlledBy(row, column, hero);
} //set tile(row, column) to be controlled by hero

void Game::Game_firstTurnSequence() {
    cout << endl;
    cout << "When you play the Game of Thrones, you win or you die." << endl;
    cout << "Let us begin, " << Game_get_hero_controlled_by_player().Hero_getName() << "." << endl;
    cout << endl;
} //sequence to be displayed during the first turn

/*
set number of turns, whether hero has arrived in a city(and display of message), check tile for dragonglass/wildfire, set tile control
print minimap
print statistics
ask what action, perform appropriate action (move, rest, consult)
resolve encounters (player and CPU), acquire heroes, move other heroes, solve random events
*/
void Game::Game_gameTurnLoop() {
    Game_setTurns(Game_getTurns() + 1); //set turn number
    Game_has_arrived_in_city(); //check if in city
    Game_checkTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column());
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        Game_set_tile_control(heroes[i].Hero_getLocation_Row(), heroes[i].Hero_getLocation_Column(), heroes[i]);
        Game_updatePoints(i); //update point totals
    }
    string turnChoice;
    cout << "-----Map-----";
    Game_getMap().Map_minimap(Game_get_hero_controlled_by_player()); //minimap
    cout << endl;
    cout << "Score: " << Game_get_hero_controlled_by_player().Hero_getScore() << endl; //display stats
    cout << "Army Size: " << Game_get_hero_controlled_by_player().Hero_getArmySize() << endl;
    cout << "Money: " << Game_get_hero_controlled_by_player().Hero_getMoney() << endl;
    cout << "Influence: " << Game_get_hero_controlled_by_player().Hero_getInfluence() << endl;
    cout << endl;
    cout << "What would you like to do?" << endl; //decision display
    cout << "1. Move" << endl;
    cout << "2. Rest" << endl;
    cout << "3. Consult with the Gods" << endl;
    cin >> turnChoice;
    while(turnChoice != "1" && turnChoice != "2" && turnChoice != "3") //user error
    {
        cout << "Please select an action." << endl;
        cin >> turnChoice;
    }
    if(turnChoice == "1") //movement
    {
        string movementChoice;
        cout << "Which way would you like to move?" << endl;
        cout << "  N  " << endl;
        cout << "W   E" << endl;
        cout << "  S  " << endl;
        cin >> movementChoice;
        cout << endl;
        while(movementChoice != "N" && movementChoice != "n" && movementChoice != "E" && movementChoice != "e" && movementChoice != "S" && movementChoice != "s" && movementChoice != "W" && movementChoice != "w")
        { //user error
            cout << "Please select a direction to move." << endl;
            cin >> movementChoice;
        }
        while(movementChoice == "N" && Game_playerCanMoveInDirection(1) == false || movementChoice == "n" && Game_playerCanMoveInDirection(1) == false || movementChoice == "S" && Game_playerCanMoveInDirection(2) == false || movementChoice == "s" && Game_playerCanMoveInDirection(2) == false || movementChoice == "W" && Game_playerCanMoveInDirection(3) == false || movementChoice == "w" && Game_playerCanMoveInDirection(3) == false || movementChoice == "E" && Game_playerCanMoveInDirection(4) == false || movementChoice == "e" && Game_playerCanMoveInDirection(4) == false)
        { //if can't move
            cout << "You can't move in that direction. Please select a direction to move." << endl;
            cin >> movementChoice;
        }
        if(movementChoice == "N" || movementChoice == "n")
        { //move direction
            Game_movePlayer(Game_returnHero_controlled_by_playerindex(), 1);
        } //move direction
        else if(movementChoice == "W" || movementChoice == "w")
        { //move direction
            Game_movePlayer(Game_returnHero_controlled_by_playerindex(), 3);
        }
        else if(movementChoice == "E" || movementChoice == "e")
        { //move direction
           Game_movePlayer(Game_returnHero_controlled_by_playerindex(), 4);
        }
        else if(movementChoice == "S" || movementChoice == "s")
        { //move direction
           Game_movePlayer(Game_returnHero_controlled_by_playerindex(), 2);
        }
    }
    else if(turnChoice == "2") //if rest
    {
        cout << "Your warriors gather their strength, but you lose valuable time." << endl;
        cout << "Others may not be so kind." << endl;
        cout << "(All warriors gain 1 strength)" << endl;
        for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
        { //adjust strength values
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorStrength(i, Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getStrength() + 1);
        }
    }
    else if(turnChoice == "3") //if 3
    {
        cout << "The Gods are pleased with your consultation." << endl;
        cout << "Your warriors gain confidence in you." << endl;
        cout << "(All warriors gain 1 morale)" << endl;
        for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
        { //adjust morale values
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorMorale(i, Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getMorale() + 1);
        }
    }
    if(Game_is_in_vicinity_hero(Game_get_hero_controlled_by_player()) == true && Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_get_death() == false)
    {
        Game_resolvePlayerEncounter(); //resolve other encounters
    }
    Game_acquireWarriors(); //grab warriors
    Game_randomEvents(); //check for events
    Game_moveOtherHeroes(); //move all other heroes
    Game_resolveCPUEncounters(); //solve other events
} //main game loop

/*recieve hero
recieve row and column locations
check a 5x5 border around given location
return true if other hero in 5x5 border, false otherwise
*/
bool Game::Game_is_in_vicinity_hero(Hero heroInput) {
    for(int row = -2; row < 3; row++) //5 row buffer
    {
        for(int column = -2; column < 3; column++) //5 column buffer
        {
            for(int i = 0; i < Game_getNumHeroes(); i++) //number of heroes
            {
                if(Game_getHero(i).Hero_getName() != Game_get_hero_controlled_by_player().Hero_getName() && Game_getHero(i).Hero_get_death() == false && Game_getHero(i).Hero_getLocation_Row() == (Game_get_hero_controlled_by_player().Hero_getLocation_Row() + row) && Game_getHero(i).Hero_getLocation_Column() == (Game_get_hero_controlled_by_player().Hero_getLocation_Column() + column))
                {
                    return true; //if find hero, return true
                }
            }
        }
    }
    return false;
} //check if heroes in vicinity of hero input

/*recieve hero
recieve row and column locations
check a 5x5 border around given location
return found hero if other hero in 5x5 border, nothing otherwise
*/
Hero Game::Game_getNearesthero(Hero heroInput) {
    for(int row = -2; row < 3; row++) //5 row buffer
    {
        for(int column = -2; column < 3; column++) //5 column buffer
        {
            for(int i = 0; i < Game_getNumHeroes(); i++) //number of heroes
            {
                if(Game_getHero(i).Hero_getName() != Game_get_hero_controlled_by_player().Hero_getName() && Game_getHero(i).Hero_get_death() == false && Game_getHero(i).Hero_getLocation_Row() == (Game_get_hero_controlled_by_player().Hero_getLocation_Row() + row) && Game_getHero(i).Hero_getLocation_Column() == (Game_get_hero_controlled_by_player().Hero_getLocation_Column() + column))
                {
                    return Game_getHero(i); //return hero
                }
            }
        }
    }
} //return hero in vicinity of heroinput

/*recieve hero
recieve row and column locations
check a 5x5 border around given location
return index of found warrior if warrior in 5x5 border, nothing otherwise
*/
int Game::Game_getNearestWarrior(Hero heroInput) {
    for(int row = -2; row < 3; row++) //5 row buffer
    {
        for(int column = -2; column < 3; column++) //5 column buffer
        {
            for(int i = 0; i < Game_getNumWarriors(); i++) //number of warriors
            {
                if(warriors[i].Warrior_getLocationColumn() == (heroInput.Hero_getLocation_Column() + column) && warriors[i].Warrior_getLocationRow() == (heroInput.Hero_getLocation_Row() + row) && warriors[i].Warrior_get_is_free() == true)
                {
                    return i; //return warrior index
                }
            }
        }
    }
} //return warrior in vicinity of heroinput

/*recieve hero
recieve row and column locations
check a 5x5 border around given location
return true if other warrior in 5x5 border, false otherwise
*/
bool Game::Game_is_in_vicinity_warrior(Hero heroInput) {
    for(int row = -2; row < 3; row++) //5 row buffer
    {
        for(int column = -2; column < 3; column++) //5 column buffer
        {
            for(int i = 0; i < Game_getNumWarriors(); i++) //number of warriors
            {
                if(warriors[i].Warrior_getLocationColumn() == (heroInput.Hero_getLocation_Column() + column) && warriors[i].Warrior_getLocationRow() == (heroInput.Hero_getLocation_Row() + row) && warriors[i].Warrior_get_is_free() == true)
                {
                    return true; //if found warrior, return true
                }
            }
        }
    }
    return false;
} //check if warriors in vicinity of heroinput

/*recieve hero
check all indeces in warriors array for that hero
return true if any of them have a ship, false otherwise
*/
bool Game::Game_warriors_have_ship(Hero hero) {
    for(int i = 0; i < 4; i++) //number of warriors
    {
        if(hero.Hero_getWarriors(i).Warrior_get_has_ship() == true) //if found ship
        {
            return true;
        }
    }
    return false;
} //check if any warriors in party have a ship

/*recieve direction (1 north, 2 south, 3 west, 4 east)
this only works for hero player is controlling
check conditions based on location
if can move in that direction, return true
if cant (water but no boat, end of map, etc.) return false
*/
bool Game::Game_playerCanMoveInDirection(int directionInput) {
    if(directionInput == 1)
    {
        if(Game_get_hero_controlled_by_player().Hero_getLocation_Row() == 0) //if last space
        {
            return false;
        }
        else if(Game_warriors_have_ship(Game_get_hero_controlled_by_player()) == false && Game_get_hero_controlled_by_player().Hero_get_has_Ship() == false && Game_getMap().Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 1)
        {
            return false; //if water tile and no ship
        }
        else
        {
            return true;
        }
    }
    if(directionInput == 2)
    {
        if(Game_get_hero_controlled_by_player().Hero_getLocation_Row() == 24) //if last space
        {
            return false;
        }
        else if(Game_warriors_have_ship(Game_get_hero_controlled_by_player()) == false && Game_get_hero_controlled_by_player().Hero_get_has_Ship() == false && Game_getMap().Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 1)
        {
            return false; //if water tile and no ship
        }
        else
        {
            return true;
        }
    }
    if(directionInput == 3)
    {
        if(Game_get_hero_controlled_by_player().Hero_getLocation_Column() == 0) //if last tile
        {
            return false; //if water tile and no ship
        }
        else if(Game_warriors_have_ship(Game_get_hero_controlled_by_player()) == false && Game_get_hero_controlled_by_player().Hero_get_has_Ship() == false && Game_getMap().Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_getType() == 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    if(directionInput == 4)
    {
        if(Game_get_hero_controlled_by_player().Hero_getLocation_Column() == 15) //if last tile
        {
            return false;
        }
        else if(Game_warriors_have_ship(Game_get_hero_controlled_by_player()) == false && Game_get_hero_controlled_by_player().Hero_get_has_Ship() == false && Game_getMap().Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_getType() == 1)
        {
            return false; //if water tile and no ship
        }
        else
        {
            return true;
        }
    }
} //check if player can move in specified direction

/*recieve index integer for hero, direction (1 north, 2 south, 3 west, 4 east)
check conditions based on location
if can move in that direction, return true
if cant (water but no boat, end of map, etc.) return false
*/
bool Game::Game_heroCanMoveInDirection(int i, int directionInput) {
    if(directionInput == 1)
    {
        if(heroes[i].Hero_getLocation_Row() == 0) //if last tile
        {
            return false;
        }
        else if(Game_warriors_have_ship(heroes[i]) == false && heroes[i].Hero_get_has_Ship() == false && Game_getMap().Map_getTile(heroes[i].Hero_getLocation_Row() - 1, heroes[i].Hero_getLocation_Column()).Tile_getType() == 1)
        {
            return false; //if water and no ship
        }
        else
        {
            return true;
        }
    }
    if(directionInput == 2)
    {
        if(heroes[i].Hero_getLocation_Row() == 24) //if last tile
        {
            return false;
        }
        else if(Game_warriors_have_ship(heroes[i]) == false && heroes[i].Hero_get_has_Ship() == false && Game_getMap().Map_getTile(heroes[i].Hero_getLocation_Row() + 1, heroes[i].Hero_getLocation_Column()).Tile_getType() == 1)
        {
            return false; //if water and no ship
        }
        else
        {
            return true;
        }
    }
    if(directionInput == 3)
    {
        if(heroes[i].Hero_getLocation_Column() == 0) //if last tile
        {
            return false;
        }
        else if(Game_warriors_have_ship(heroes[i]) == false && heroes[i].Hero_get_has_Ship() == false && Game_getMap().Map_getTile(heroes[i].Hero_getLocation_Row(), heroes[i].Hero_getLocation_Column() - 1).Tile_getType() == 1)
        {
            return false; //if water and no ship
        }
        else
        {
            return true;
        }
    }
    if(directionInput == 4)
    {
        if(heroes[i].Hero_getLocation_Column() == 15) //if last tile
        {
            return false;
        }
        else if(Game_warriors_have_ship(heroes[i]) == false && heroes[i].Hero_get_has_Ship() == false && Game_getMap().Map_getTile(heroes[i].Hero_getLocation_Row(), heroes[i].Hero_getLocation_Column() + 1).Tile_getType() == 1)
        {
            return false; //if water tile and no ship
        }
        else
        {
            return true;
        }
    }
} //check if hero at index i can move in specified direction

int Game::Game_returnHero_controlled_by_playerindex() {
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        if(heroes[i].Hero_get_is_controlled_by_player() == true)
        {
            return i; //return index for hero controlled by player
        }
    }
} //return index number of hero controlled by player

/*recieve index integer and direction (1 north, 2 south, 3 west, 4 east)
this only works for hero player is controlling
check conditions based on location
if can move in that direction, move and adjust statistics if they don't already control it
*/
void Game::Game_movePlayer(int indexInput, int directionInput) {
    if(directionInput == 1)
    {
        if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 1 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile before and water
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 2 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and land
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 20);
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 3 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and city
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getMoney());
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() - 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getArmy_Size());
        }
        heroes[indexInput].Hero_setLocation_Row(heroes[indexInput].Hero_getLocation_Row() - 1); //move player
    }
    else if(directionInput == 2)
    {
        if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 1 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and water
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 2 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and land
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 20);
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 3 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to  tile and city
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getMoney());
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row() + 1, Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getArmy_Size());
        }
        heroes[indexInput].Hero_setLocation_Row(heroes[indexInput].Hero_getLocation_Row() + 1); // move player
    }
    else if(directionInput == 3)
    {
        if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_getType() == 1 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and water
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_getType() == 2 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and land
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 20);
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_getType() == 3 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and city
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_getMoney());
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() - 1).Tile_getArmy_Size());
        }
        heroes[indexInput].Hero_setLocation_Column(heroes[indexInput].Hero_getLocation_Column() - 1); //move player
    }
    else if(directionInput == 4)
    {
        if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_getType() == 1 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and water
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_getType() == 2 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and land
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + 20);
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + 10);
        }
        else if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_getType() == 3 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_get_hero_controlled_by().Hero_getName())
        { //if havent been to tile and city
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_getMoney());
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column() + 1).Tile_getArmy_Size());
        }
        heroes[indexInput].Hero_setLocation_Column(heroes[indexInput].Hero_getLocation_Column() + 1); //move player
    }
} //move hero at index indexInput in directionInput

void Game::Game_setInfluence(int indexInput, int influenceInput) {
    heroes[indexInput].Hero_setInfluence(influenceInput);
} //set influence of hero at indexInput to influenceInput

void Game::Game_setMoney(int indexInput, int moneyInput) {
    heroes[indexInput].Hero_setMoney(moneyInput);
} //set money of hero at indexInpyt to moneyInput

void Game::Game_setArmySize(int indexInput, int armySizeInput) {
    heroes[indexInput].Hero_setArmySize(armySizeInput);
} //set army size of hero at indexInput to moneyInput

void Game::Game_setPoints(int indexInput, int pointsInput) {
    heroes[indexInput].Hero_setScore(pointsInput);
} //set points of hero at indexInput to pointsInput

void Game::Game_set_is_dead(int indexInput, bool deathInput) {
    heroes[indexInput].Hero_set_death(deathInput);
} //set if hero at indexInput is dead based on deathInput

void Game::Game_setWarriors(int indexInput, int warriorIndexInput, Warrior warrior) {
    heroes[indexInput].Hero_setWarriors(warrior, warriorIndexInput);
} //set warriors for hero at indexInput at warriorIndexInput to warrior

/*
Recieve Hero input
search heroes vector for hero question
return index number of hero
*/
int Game::Game_returnHeroIndex(Hero hero) {
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        if(heroes[i].Hero_getName() == hero.Hero_getName()) //if found hero
        {
            return i;
        }
    }
} //return index of a specific hero

/*
Recieve Hero input
search warriors array for has_wildfire() == true
if finds warrior with woldfire, return true
if not return false
*/
bool Game::Game_hasWildfire(Hero hero) {
    for(int i = 0; i < 4; i++)
    {
        if(hero.Hero_getWarriors(i).Warrior_get_has_wildfire() == true) //if one hero has wildfire
        {
            return true;
        }
    }
    return false;
} //check if hero has wildfire in party

/*Big boy function
print encounter message, ask for desired course of action
calculate probabilities based on each course of action
if win, change statistics and give hero option to steal warriors
steal heroes based on number of warriors
if lose, change statistics, print message, kill
*/
void Game::Game_resolvePlayerEncounter() {
    string encounterChoice;
    cout << "You have encountered " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName() << "!" << endl;
    cout << "What would you like to do?" << endl;
    cout << endl;
    cout << "1. Give a speech" << endl; //encounter choice
    cout << "2. Buy them outright" << endl;
    cout << "3. Battle" << endl;
    cin >> encounterChoice;
    while(encounterChoice != "1" && encounterChoice != "2" && encounterChoice != "3")
    {
        cout << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName() << " is waiting..." << endl;
        cin >> encounterChoice;
    }
    if(encounterChoice == "1")
    {
        double morale = 1 - (Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(0).Warrior_getMorale() / 100);
        double persuasion = Game_get_hero_controlled_by_player().Hero_getInfluence() / 1600;
        double probability = (morale*persuasion)*10000; //calculate probability
        int decision = Game_randomInteger(); //produce integer
        if(decision <= probability)
        {
            cout << "Your speech was a success! You have defeated your opponent." << endl;
            cout << "Now you get all of their stuff." << endl;
            Game_setInfluence(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getInfluence() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getInfluence());
            Game_setMoney(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getMoney() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getMoney());
            Game_setArmySize(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getArmySize() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getArmySize());
            if(Game_get_hero_controlled_by_player().Hero_getNumWarriors() == 4 && Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors() != 0)
            {
                string warriorChoice;
                cout << "You have too many warriors. Would you like to steal one of your opponents warriors?" << endl;
                cout << "You would have to replace one of your own. (Y/N)" << endl;
                cin >> warriorChoice;
                while(warriorChoice != "Y" && warriorChoice != "y" && warriorChoice != "N" && warriorChoice != "n") //user error
                {
                    cout << "I don't have all day." << endl;
                    cin >> warriorChoice;
                }
                if(warriorChoice == "Y" || warriorChoice == "y")
                {
                    string WarriorChoice1;
                    cout << "Which warrior would you like to steal?" << endl; //choose warrior
                    for(int i = 0; i < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> WarriorChoice1;
                    while(WarriorChoice1 != "1" && WarriorChoice1 != "2" && WarriorChoice1 != "3" && WarriorChoice1 != "4")
                    { //ig user error
                        cout << "Please input the number of the warrior you want to steal." << endl;
                        cin >> WarriorChoice1;
                    }
                    string warriorChoice2;
                    cout << "Which of your warriors would you like to replace?" << endl;
                    for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> warriorChoice2;
                    while(warriorChoice2 != "1" && warriorChoice2 != "2" && warriorChoice2 != "3" && warriorChoice2 != "4")
                    { //which warrior to replace
                        cout << "Please input the number of the warrior you want to replace." << endl;
                        cin >> warriorChoice2;
                    }
                    Game_setWarriors(Game_returnHeroIndex(Game_get_hero_controlled_by_player()), stoi(warriorChoice2) - 1, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(stoi(WarriorChoice1) - 1));
                }
                else if(warriorChoice == "N" || warriorChoice == "n")
                {
                    cout << endl;
                }
            }
            else if((Game_get_hero_controlled_by_player().Hero_getNumWarriors() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors()) > 4)
            {
                string warriorChoice;
                cout << "Would you like to steal one of your opponents warriors? (Y/N)" << endl; //whether to steal
                while(warriorChoice != "Y" && warriorChoice != "y" && warriorChoice != "N" && warriorChoice != "n")
                {
                    cout << "I don't have all day." << endl;
                    cin >> warriorChoice;
                }
                if(warriorChoice == "Y" || warriorChoice == "y")
                {
                    string WarriorChoice1;
                    cout << "Which warrior would you like to steal?" << endl; //choose warrior to replace
                    for(int i = 0; i < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> WarriorChoice1;
                    while(WarriorChoice1 != "1" && WarriorChoice1 != "2" && WarriorChoice1 != "3" && WarriorChoice1 != "4")
                    {
                        cout << "Please input the number of the warrior you want to steal." << endl;
                        cin >> WarriorChoice1;
                    }
                    string warriorChoice2;
                    cout << "Which of your warriors would you like to replace?" << endl;
                    for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> warriorChoice2;
                    while(warriorChoice2 != "1" && warriorChoice2 != "2" && warriorChoice2 != "3" && warriorChoice2 != "4")
                    {
                        cout << "Please input the number of the warrior you want to replace." << endl;
                        cin >> warriorChoice2;
                    }
                    Game_setWarriors(Game_returnHeroIndex(Game_get_hero_controlled_by_player()), stoi(warriorChoice2) - 1, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(stoi(WarriorChoice1) - 1));
                }
                else if(warriorChoice == "N" || warriorChoice == "n")
                {
                    cout << endl;
                }
            }
            else
            {
                cout << endl;
                int j = 0;
                for(int i = Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i < 4; i++)
                {
                    Game_setWarriors(Game_returnHero_controlled_by_playerindex(), i, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(j));
                    if(j < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors())
                    {
                        cout << "You have acquired " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(j).Warrior_getName() << "!" << endl;
                    }
                    j++;
                }
            }
            cout << endl; //when fefeated, death message
            cout << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName() << " has retired." << endl;
            cout << endl;
            for(int i = 0; i < 25; i++)
            {
                for(int j = 0; j < 16; j++) //take control of all tiles
                {
                    if(Game_getMap().Map_getTile(i,j).Tile_get_hero_controlled_by().Hero_getName() == Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName())
                    {
                        Game_map.Map_setHeroControlledBy(i,j,Game_get_hero_controlled_by_player());
                    }
                }
            }
            Game_set_is_dead(Game_returnHeroIndex(Game_getNearesthero(Game_get_hero_controlled_by_player())), true);
        }
        else if(decision > probability)
        {
            cout << "Your speech was a failure! You escape, but your influence is no more." << endl; //if speech failure
            cout << endl;
            Game_setInfluence(Game_returnHero_controlled_by_playerindex(), (Game_get_hero_controlled_by_player().Hero_getInfluence() / 2));
        }
    }
    else if(encounterChoice == "2")
    {
        double loyalty = Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(0).Warrior_getLoyalty();
        double money = Game_get_hero_controlled_by_player().Hero_getMoney();
        double probability = ((1-(loyalty/100))*(money/17800)) * 10000;
        int decision = Game_randomInteger();
        if(decision <= probability)
        {
            cout << "Your purchase was a success! You have defeated your opponent." << endl;
            cout << "Now you get all of their stuff." << endl;
            Game_setInfluence(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getInfluence() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getInfluence());
            Game_setMoney(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getMoney() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getMoney());
            Game_setArmySize(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getArmySize() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getArmySize());
            if(Game_get_hero_controlled_by_player().Hero_getNumWarriors() == 4 && Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors() != 0)
            {
                string warriorChoice;
                cout << "You have too many warriors. Would you like to steal one of your opponents warriors?" << endl;
                cout << "You would have to replace one of your own. (Y/N)" << endl;
                cin >> warriorChoice;
                while(warriorChoice != "Y" && warriorChoice != "y" && warriorChoice != "N" && warriorChoice != "n")
                {
                    cout << "I don't have all day." << endl;
                    cin >> warriorChoice;
                }
                if(warriorChoice == "Y" || warriorChoice == "y")
                {
                    string WarriorChoice1;
                    cout << "Which warrior would you like to steal?" << endl;
                    for(int i = 0; i < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> WarriorChoice1;
                    while(WarriorChoice1 != "1" && WarriorChoice1 != "2" && WarriorChoice1 != "3" && WarriorChoice1 != "4")
                    {
                        cout << "Please input the number of the warrior you want to steal." << endl;
                        cin >> WarriorChoice1;
                    }
                    string warriorChoice2;
                    cout << "Which of your warriors would you like to replace?" << endl;
                    for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> warriorChoice2;
                    while(warriorChoice2 != "1" && warriorChoice2 != "2" && warriorChoice2 != "3" && warriorChoice2 != "4")
                    {
                        cout << "Please input the number of the warrior you want to replace." << endl;
                        cin >> warriorChoice2;
                    }
                    Game_setWarriors(Game_returnHeroIndex(Game_get_hero_controlled_by_player()), stoi(warriorChoice2) - 1, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(stoi(WarriorChoice1) - 1));
                }
                else if(warriorChoice == "N" || warriorChoice == "n")
                {
                    cout << endl;
                }
            }
            else if((Game_get_hero_controlled_by_player().Hero_getNumWarriors() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors()) > 4)
            {
                string warriorChoice;
                cout << "Would you like to steal one of your opponents warriors? (Y/N)" << endl;
            }
            else
            {
                cout << endl;
                int j = 0;
                for(int i = Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i < 4; i++)
                {
                    Game_setWarriors(Game_returnHero_controlled_by_playerindex(), i, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(j));
                    if(j < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors())
                    {
                        cout << "You have acquired " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(j).Warrior_getName() << "!" << endl;
                    }
                    j++;
                }
            }
            cout << endl;
            cout << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName() << " has retired." << endl;
            cout << endl;
            for(int i = 0; i < 25; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    if(Game_getMap().Map_getTile(i,j).Tile_get_hero_controlled_by().Hero_getName() == Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName())
                    {
                        Game_map.Map_setHeroControlledBy(i,j,Game_get_hero_controlled_by_player());
                    }
                }
            }
            Game_set_is_dead(Game_returnHeroIndex(Game_getNearesthero(Game_get_hero_controlled_by_player())), true);
        }
        else if(decision > probability)
        {
            cout << "Your purchase attempt was a failure! You escape, but your gold reserves are decimated." << endl;
            cout << endl;
            Game_setMoney(Game_returnHero_controlled_by_playerindex(), (Game_get_hero_controlled_by_player().Hero_getInfluence() / 2));
        }
    }
    else if(encounterChoice == "3")
    {
        if(Game_get_hero_controlled_by_player().Hero_getNumWarriors() == 0)
        {
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_set_death(true);
            return;
        }
        double strength;
        double armySize;
        string warriorChoice3 = "0"; //battle probability
        int wildFireUse = 0;
        {
        if(Game_get_hero_controlled_by_player().Hero_has_wildfire_in_party() == true) //for wildfire
        {
            string wildfireChoice;
            cout << "It appears you have Wildfire at your disposal. Would you like to use it? (Y/N)" << endl;
            cin >> wildfireChoice;
            while(wildfireChoice != "Y" && wildfireChoice != "y" && wildfireChoice != "N" && wildfireChoice != "n")
            {
                cout << "You're in battle, you cannot hesitate." << endl;
                cin >> wildfireChoice;
            }
            if(wildfireChoice == "y" || wildfireChoice == "Y")
            {
                wildFireUse = 1;
                for(int i = 0; i < 4; i++)
                {
                    heroes[Game_returnHeroIndex(Game_get_hero_controlled_by_player())].Hero_set_has_wildfire(i,false);
                }
            }
            else if(wildfireChoice == "n" || wildfireChoice == "N")
            {
                wildFireUse = 0;
            }
        }
        if(Game_get_hero_controlled_by_player().Hero_getNumWarriors() > 0 && wildFireUse == 0) //if not wildfire
        {
            cout << "Which of your warriors will represent you in battle?" << endl;
            for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
            {
                cout << (i + 1) << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
            }
            cin >> warriorChoice3;
            while(warriorChoice3 != "1" && warriorChoice3 != "2" && warriorChoice3 != "3" && warriorChoice3 != "4" || stoi(warriorChoice3) > Game_get_hero_controlled_by_player().Hero_getNumWarriors())
            {
                cout << "Please choose a warrior to represent you." << endl;
                cin >> warriorChoice3;
            }
        }
        strength = Game_get_hero_controlled_by_player().Hero_getWarriors(stoi(warriorChoice3) - 1).Warrior_getStrength();
        armySize = Game_get_hero_controlled_by_player().Hero_getArmySize();
        double probability = (strength*armySize);
        int decision1 = Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(0).Warrior_getStrength();
        int decision2 = Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getArmySize();
        int decision = decision1*decision2;
        if(decision <= probability || wildFireUse == 1)
        {
            cout << "You have defeated " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName() << "!" << endl;
            cout << "Now you get all of their stuff." << endl;
            Game_setInfluence(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getInfluence() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getInfluence());
            Game_setMoney(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getMoney() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getMoney());
            Game_setArmySize(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getArmySize() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getArmySize());
            if(Game_get_hero_controlled_by_player().Hero_getNumWarriors() == 4 && Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors() != 0)
            {
                string warriorChoice;
                cout << "You have too many warriors. Would you like to steal one of your opponents warriors?" << endl;
                cout << "You would have to replace one of your own. (Y/N)" << endl;
                cin >> warriorChoice;
                while(warriorChoice != "Y" && warriorChoice != "y" && warriorChoice != "N" && warriorChoice != "n")
                {
                    cout << "I don't have all day." << endl;
                    cin >> warriorChoice;
                }
                if(warriorChoice == "Y" || warriorChoice == "y")
                {
                    string WarriorChoice1;
                    cout << "Which warrior would you like to steal?" << endl;
                    for(int i = 0; i < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> WarriorChoice1;
                    while(WarriorChoice1 != "1" && WarriorChoice1 != "2" && WarriorChoice1 != "3" && WarriorChoice1 != "4")
                    {
                        cout << "Please input the number of the warrior you want to steal." << endl;
                        cin >> WarriorChoice1;
                    }
                    string warriorChoice2;
                    cout << "Which of your warriors would you like to replace?" << endl;
                    for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> warriorChoice2;
                    while(warriorChoice2 != "1" && warriorChoice2 != "2" && warriorChoice2 != "3" && warriorChoice2 != "4")
                    {
                        cout << "Please input the number of the warrior you want to replace." << endl;
                        cin >> warriorChoice2;
                    }
                    Game_setWarriors(Game_returnHeroIndex(Game_get_hero_controlled_by_player()), stoi(warriorChoice2) - 1, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(stoi(WarriorChoice1) - 1));
                }
                else if(warriorChoice == "N" || warriorChoice == "n")
                {
                    cout << endl;
                }
            }
            else if((Game_get_hero_controlled_by_player().Hero_getNumWarriors() + Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors()) > 4)
            {
                string warriorChoice;
                cout << "Would you like to steal one of your opponents warriors? (Y/N)" << endl;
                cin >> warriorChoice;
                while(warriorChoice != "Y" && warriorChoice != "y" && warriorChoice != "N" && warriorChoice != "n")
                {
                    cout << "I don't have all day." << endl;
                    cin >> warriorChoice;
                }
                if(warriorChoice == "Y" || warriorChoice == "y")
                {
                    string WarriorChoice1;
                    cout << "Which warrior would you like to steal?" << endl;
                    for(int i = 0; i < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> WarriorChoice1;
                    while(WarriorChoice1 != "1" && WarriorChoice1 != "2" && WarriorChoice1 != "3" && WarriorChoice1 != "4")
                    {
                        cout << "Please input the number of the warrior you want to steal." << endl;
                        cin >> WarriorChoice1;
                    }
                    string warriorChoice2;
                    cout << "Which of your warriors would you like to replace?" << endl;
                    for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                    {
                        cout << i + 1 << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
                    }
                    cin >> warriorChoice2;
                    while(warriorChoice2 != "1" && warriorChoice2 != "2" && warriorChoice2 != "3" && warriorChoice2 != "4")
                    {
                        cout << "Please input the number of the warrior you want to replace." << endl;
                        cin >> warriorChoice2;
                    }
                    Game_setWarriors(Game_returnHeroIndex(Game_get_hero_controlled_by_player()), stoi(warriorChoice2) - 1, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(stoi(WarriorChoice1) - 1));
                }
                else if(warriorChoice == "N" || warriorChoice == "n")
                {
                    cout << endl;
                }
            }
            else
            {
                cout << endl;
                int j = 0;
                for(int i = Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i < 4; i++)
                {
                    Game_setWarriors(Game_returnHero_controlled_by_playerindex(), i, Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(j));
                    if(j < Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getNumWarriors())
                    {
                        cout << "You have acquired " << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getWarriors(j).Warrior_getName() << "!" << endl;
                    }
                    j++;
                }
            }
            cout << endl;
            cout << Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName() << " has retired." << endl;
            cout << endl;
            for(int i = 0; i < 25; i++)
            {
                for(int j = 0; j < 16; j++)
                {
                    if(Game_getMap().Map_getTile(i,j).Tile_get_hero_controlled_by().Hero_getName() == Game_getNearesthero(Game_get_hero_controlled_by_player()).Hero_getName())
                    {
                        Game_map.Map_setHeroControlledBy(i,j,Game_get_hero_controlled_by_player()); //set tiles controlled by
                    }
                }
            }
            Game_set_is_dead(Game_returnHeroIndex(Game_getNearesthero(Game_get_hero_controlled_by_player())), true); //set hero as dead
        }
        else if(decision > probability)
        {
            cout << "You have been defeated in battle." << endl;
            cout << endl;
            Game_set_is_dead(Game_returnHero_controlled_by_playerindex(), true); //set player as dead
        }
    }
    }
} //resolve player encounters (stealing warriors, calculating probability, etc.)

int Game::Game_randomInteger() {
    return rand() % 10000 + 1;
} //produce a random integer between 1 and 10000

void Game::Game_gameDeath() {
    cout << endl;
    cout << "Valar Morghulis." << endl;
    cout << endl;
    cout << "You have been defeated. The Game of Thrones will continue, and another will claim the throne." << endl;
    cout << "Thanks for playing." << endl;
} //sequence to display if the player dies

/* Input inex of hero to update
traverse map, if hero_controlled_by() == heroes[index], add points associated with that tile
do this for each hero at the end of the turn
*/
void Game::Game_updatePoints(int index) {
    heroes[index].Hero_setScore(0);
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 16; j++) //traverse map
        {
            if(Game_map.Map_getTile(i,j).Tile_get_hero_controlled_by().Hero_getName() == heroes[index].Hero_getName()) //if hero controls tile
            {
                if(Game_map.Map_getTile(i,j).Tile_getType() == 1)
                {
                    heroes[index].Hero_setScore(heroes[index].Hero_getScore() + 1); //if water
                }
                else if(Game_map.Map_getTile(i,j).Tile_getType() == 2)
                {
                    heroes[index].Hero_setScore(heroes[index].Hero_getScore() + 2); //if land
                }
                else if(Game_map.Map_getTile(i,j).Tile_getType() == 3)
                {
                    heroes[index].Hero_setScore(heroes[index].Hero_getScore() + Game_map.Map_getTile(i,j).Tile_getPoints()); //if city
                }
            }
        }
    }
} //traverse map to determine number of points

/* Dragonglass/wildfire acquisition system
Input row and column, check tile at coordinates
If found dragonglass, output message and give option to add to a warrior. Remove from tile
If found wildfire, output message and give option to add to warrior. Do not remove from tile
If found either and no warriors to equip, display message and tell hero to return later
*/
void Game::Game_checkTile(int rowInput, int columnInput) {
    if(Game_map.Map_getTile(rowInput, columnInput).Tile_get_has_dragonglass() == true && Game_get_hero_controlled_by_player().Hero_getNumWarriors() > 0) //if has dragonglass and a warrior
    {
        string dragonglassChoice;
        cout << "You have stumbled upon dragonglass! Select a warrior to equip it." << endl;
        for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
        { //cout warriors
            cout << i + 1 << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
        }
        cin >> dragonglassChoice;
        while(dragonglassChoice != "1" && dragonglassChoice != "2" && dragonglassChoice != "3" && dragonglassChoice != "4" || stoi(dragonglassChoice) > Game_get_hero_controlled_by_player().Hero_getNumWarriors())
        { //user error
            cout << "Please choose a warrior to equip with dragonglass. You'll need it..." << endl;
            cin >> dragonglassChoice;
        }
        if(dragonglassChoice == "1" || dragonglassChoice == "2" || dragonglassChoice == "3" || dragonglassChoice == "4")
        { //set dragonglass
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_set_has_dragonglass(stoi(dragonglassChoice) - 1, true);
            Game_map.Map_setDragonglass(rowInput, columnInput, false);
        }
    }
    else if(Game_map.Map_getTile(rowInput, columnInput).Tile_get_has_dragonglass() == true && Game_get_hero_controlled_by_player().Hero_getNumWarriors() == 0)
    { //if doesn't have hero
        cout << "You've stumbled upon dragonglass! Unfortunately, you have no heroes to equip it." << endl;
        cout << "Come back when you have a suitable warrior." << endl;
    }
    if(Game_map.Map_getTile(rowInput, columnInput).Tile_get_has_wildfire() == true && Game_get_hero_controlled_by_player().Hero_getNumWarriors() > 0 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(rowInput, columnInput).Tile_get_hero_controlled_by().Hero_getName())
    { //if find wildfire and has warrior
        string wildfireChoice;
        cout << "You have been awarded Wildfire! Please choose a warrior to equip it." << endl;
        for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
        { //cout warriors
            cout << i + 1 << ". " << Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getName() << endl;
        }
        cin >> wildfireChoice;
        while(wildfireChoice != "1" && wildfireChoice != "2" && wildfireChoice != "3" && wildfireChoice != "4" || stoi(wildfireChoice) > Game_get_hero_controlled_by_player().Hero_getNumWarriors())
        {  //if user error
            cout << "Please choose a warrior to equip with Wildfire." << endl;
            cin >> wildfireChoice;
        }
        if(wildfireChoice == "1" || wildfireChoice == "2" || wildfireChoice == "3" || wildfireChoice == "4")
        { //set wildfire
            heroes[Game_returnHero_controlled_by_playerindex()].Hero_set_has_wildfire(stoi(wildfireChoice) - 1, true);
        }
    }
    else if(Game_map.Map_getTile(rowInput, columnInput).Tile_get_has_wildfire() == true && Game_get_hero_controlled_by_player().Hero_getNumWarriors() == 0 && Game_get_hero_controlled_by_player().Hero_getName() != Game_map.Map_getTile(rowInput, columnInput).Tile_get_hero_controlled_by().Hero_getName())
    {
        cout << "You've stumbled upon wildfire! Unfortunately, you have no heroes to equip it." << endl;
    }
} //check tile rowInput, columnInput for dragonglass and wildfire

/* randomize row and column coordinates 5 times, add dragonglass to those locations
if location already has dragonglass, randomize coordinates again until find and empty tile
*/
void Game::Game_scatter_dragonglass() {
    for(int i = 0; i < 5; i++) //5 dragonglass pieces
    {
        int row = rand() % 24 + 1;
        int column = rand() % 15 + 1;
        while(Game_map.Map_getTile(row,column).Tile_get_has_dragonglass() == true) //if already has dragonglass
        {
            row = rand() % 24 + 1;
            column = rand() % 15 + 1;
        }
        Game_map.Map_setDragonglass(row, column, true); //set is true
    }
} //randomly scatter dragonglass in 5 locations

/*Create new warrior "dragons"
add statistics, display messages
if daenarys has 4 heroes, adjust statistics and print message
print message indicating 10 turns
Kill stannis, display message
Sansa acquires Arya, remove arya from other control
Cersei loses jaime, jaime becomes free and goes back to original location
*/
void Game::Game_preset_ten_turns() {
    Warrior W1; //new dragons warrior
    W1.Warrior_setName("Dragons");
    W1.Warrior_setLoyalty(100);
    W1.Warrior_setStrength(180);
    W1.Warrior_setMorale(80);
    W1.Warrior_set_is_free(false);
    W1.Warrior_set_has_dragonglass(false);
    W1.Warrior_set_has_ship(true);
    W1.Warrior_set_has_wildfire(false);
    heroes[5].Hero_setArmySize(heroes[5].Hero_getArmySize() + 5000);
    if(Game_returnHero_controlled_by_playerindex() == 5)
    {
        cout << "You have embraced the flames, and become the mother of dragons." << endl;
        cout << "They have granted you immense power." << endl;
        cout << endl;
    }
    else
    {
        cout << endl;
        cout << "You hear rumours of a great army in the east. Thousands of unsullied." << endl;
        cout << "They are accompanied by... dragons? Surely this is just rumour..." << endl;
        cout << endl;
    }
    if(Game_getHero(5).Hero_getNumWarriors() == 4) //id danaerys already hsa 4 warriors
    {
        if(Game_returnHero_controlled_by_playerindex() == 5)
        {
        cout << "Your dragons became hungry, and consumed " << heroes[5].Hero_getWarriors(3).Warrior_getName() << "." << endl;
        cout << "Feeding them has made them stronger." << endl;
        }
        W1.Warrior_setLoyalty(110);
        W1.Warrior_setStrength(198);
        W1.Warrior_setMorale(88);
        heroes[5].Hero_setWarriors(W1, 3); //change statistice
    }
    else
    {
        heroes[5].Hero_setWarriors(W1, Game_getHero(5).Hero_getNumWarriors()); //set dragon
    }
    if(Game_returnHero_controlled_by_playerindex() != 1 && heroes[1].Hero_get_death() == false) //if stannis can die
    {
        string respect;
        for(int i = 0; i > 4; i++)
        {
            heroes[1].Hero_getWarriors(i).Warrior_set_is_free(true); //stannis' heroes are free
        }
        heroes[1].Hero_set_death(true); //kill stannis
        cout << "Stannis has been consumed by his demons" << endl;
        cout << "Press F to pay respects." << endl;
        cin >> respect;
        while(respect != "f" && respect != "F") //if user erorr
        {
            cout << "Have you no respect?! Press F to pay respects!" << endl;
            cin >> respect;
        }
        if(respect == "F" || respect == "f")
        {
            cout << "Mood." << endl;
            cout << endl;
        }
    }
    else if(Game_returnHero_controlled_by_playerindex() == 1 && heroes[1].Hero_get_death() == false)
    {
        heroes[1].Hero_set_death(true); //kill stannis
    }
    if(heroes[3].Hero_getNumWarriors() < 4 && heroes[3].Hero_getWarriors(0).Warrior_getName() != "Arya Stark" && heroes[3].Hero_getWarriors(1).Warrior_getName() != "Arya Stark" && heroes[3].Hero_getWarriors(2).Warrior_getName() != "Arya Stark" && heroes[3].Hero_getWarriors(3).Warrior_getName() != "Arya Stark")
    {
        for(int i = 0; i < Game_getNumHeroes(); i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(heroes[i].Hero_getWarriors(j).Warrior_getName() == "Arya Stark") //remove arya from other heroes
                {
                    heroes[i].Hero_setWarriors(Warrior(), j);
                    heroes[i].Hero_setWarriors(heroes[i].Hero_getWarriors(1), 0);
                    heroes[i].Hero_setWarriors(heroes[i].Hero_getWarriors(2), 1);
                    heroes[i].Hero_setWarriors(heroes[i].Hero_getWarriors(3), 2);
                    heroes[i].Hero_setWarriors(Warrior(), 3); //add arya to sansa
                }
            }
        }
        if(Game_returnHero_controlled_by_playerindex() == 3) //if playing as sansa
        {
            cout << endl;
            cout << "You have acquired Arya Stark!" << endl;
            heroes[3].Hero_setWarriors(warriors[9], heroes[3].Hero_getNumWarriors());
            warriors[9].Warrior_set_is_free(false);
        }
        else
        {
            heroes[3].Hero_setWarriors(warriors[9], heroes[3].Hero_getNumWarriors());
            warriors[9].Warrior_set_is_free(false); // arya is not free
        }
    }
    if(heroes[0].Hero_getWarriors(0).Warrior_getName() == "Jaime Lannister") //find jaime
    {
        heroes[0].Hero_setWarriors(Warrior(), 0); //remove jaime, move other warriors up
        heroes[0].Hero_setWarriors(heroes[0].Hero_getWarriors(1), 0);
        heroes[0].Hero_setWarriors(heroes[0].Hero_getWarriors(2), 1);
        heroes[0].Hero_setWarriors(heroes[0].Hero_getWarriors(3), 2);
        heroes[0].Hero_setWarriors(Warrior(), 3);
        warriors[7].Warrior_set_is_free(true);
        if(Game_returnHero_controlled_by_playerindex() == 0) //if playing as cersei
        {
            cout << "You have lost Jaime Lannister." << endl;
        }
    }
} //changes made at 10 turns

/* If arrived in a city and do not already control the city, initialize events
50/50 chance to buy knights vs hear rumors
if buy knights, opportunity to buy knights for the cost of 20 gold each
If hear rumors, find closest hero and display how many "day" they are away
*/
void Game::Game_has_arrived_in_city() {
    if(Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getType() == 3 && Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_get_hero_controlled_by().Hero_getName() != Game_get_hero_controlled_by_player().Hero_getName())
    {
        cout << "You have arrived in " << Game_map.Map_getTile(Game_get_hero_controlled_by_player().Hero_getLocation_Row(), Game_get_hero_controlled_by_player().Hero_getLocation_Column()).Tile_getName() << "!" << endl;
        int randomChoice = rand() % 2 + 1; //event probability
        if(randomChoice == 1)
        {
            string rumorChoice;
            cout << "Would you like to hear rumors? (Y/N)" << endl;
            cin >> rumorChoice;
            while(rumorChoice != "Y" && rumorChoice != "y" && rumorChoice != "N" && rumorChoice != "n") //user error
            {
                cout << "Well, would you??" << endl;
                cin >> rumorChoice;
            }
            if(rumorChoice == "Y" || rumorChoice == "y")
            {
                int distanceRow = Game_find_nearest_hero().Hero_getLocation_Row() - Game_get_hero_controlled_by_player().Hero_getLocation_Row();
                int distanceColumn = Game_find_nearest_hero().Hero_getLocation_Column() - Game_get_hero_controlled_by_player().Hero_getLocation_Column();
                if(distanceRow < 0)
                {
                    distanceRow = distanceRow * -1;
                }
                if(distanceColumn < 0)
                {
                    distanceColumn = distanceColumn * -1;
                }
                int distance = distanceRow + distanceColumn; //calculate distance
                cout << Game_find_nearest_hero().Hero_getName() << " is " << distance << " days away." << endl;
                cout << endl;
            }
        }
        else if(randomChoice == 2)
        {
            string knightChoice;
            cout << "Would you like to buy knights? (Y/N)" << endl;
            cin >> knightChoice;
            while(knightChoice != "Y" && knightChoice != "y" && knightChoice != "N" && knightChoice != "n") //user error
            {
                cout << "The Lords cannot wait all day." << endl;
                cin >> knightChoice;
            }
            if(knightChoice == "Y" || knightChoice == "y")
            {
                string knightsQuantity = "0";
                cout << "How many nights would you like to buy? Each is 20 Gold" << endl;
                cin >> knightsQuantity;
                for(int i = 0; i < knightsQuantity.length(); i++)
                {
                    if(knightsQuantity[i] != '0' && knightsQuantity[i] != '1' && knightsQuantity[i] != '2' && knightsQuantity[i] != '3' && knightsQuantity[i] != '4' && knightsQuantity[i] != '5' && knightsQuantity[i] != '6' && knightsQuantity[i] != '7' && knightsQuantity[i] != '8' && knightsQuantity[i] != '9')
                    { //user error
                        knightsQuantity = "1000000";
                    }
                }
                while(stoi(knightsQuantity) > (Game_get_hero_controlled_by_player().Hero_getMoney() / 20)) //user error
                {
                    cout << "You cannot buy those knights. Please select a quantity of nights to buy." << endl;
                    cin >> knightsQuantity;
                }
                if(stoi(knightsQuantity) < (Game_get_hero_controlled_by_player().Hero_getMoney() / 20)) //
                {
                    int moneySpent = stoi(knightsQuantity)*20; //money spending
                    heroes[Game_returnHero_controlled_by_playerindex()].Hero_setMoney(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getMoney() - moneySpent);
                    heroes[Game_returnHero_controlled_by_playerindex()].Hero_setArmySize(heroes[Game_returnHero_controlled_by_playerindex()].Hero_getArmySize() + stoi(knightsQuantity));
                }
            }
        }
    }
} //city arrival sequence (rumors, knight purchase)

/* Find the closest hero to the player by comparing the differences between row/column locations for all heroes
return hero with smallest combined distance
*/
Hero Game::Game_find_nearest_hero() {
    int distances[6]; //distances for all heroes
    int minimumDistance = 999999; //distance to reduce
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        if(i != Game_returnHero_controlled_by_playerindex() && heroes[i].Hero_get_death() == false) //if hero isn't dead
        {
            int totalDistance;
            int rowDistance;
            int columnDistance;
            rowDistance = heroes[i].Hero_getLocation_Row() - Game_get_hero_controlled_by_player().Hero_getLocation_Row();
            columnDistance = heroes[i].Hero_getLocation_Column() - Game_get_hero_controlled_by_player().Hero_getLocation_Column();
            if(rowDistance < 0)
            {
                rowDistance = rowDistance * -1; //if negative ditance, make positive
            }
            if(columnDistance < 0)
            {
                columnDistance = columnDistance * -1; //if negative distace, make positive
            }
            totalDistance = rowDistance + columnDistance;
            distances[i] = totalDistance; //total distance
        }
        else
        {
            distances[i] = 1000000; //if dead
        }
    }
    for(int j = 0; j < 6; j++)
    {
        if(distances[j] < minimumDistance)
        {
            minimumDistance = distances[j]; //find smallest distance
        }
    }
    for(int k = 0; k < 6; k++)
    {
        if(minimumDistance == distances[k])
        {
            return heroes[k]; //return smallest distance
        }
    }
} //find closest hero to player (for rumors)

/* Initialization of white walker sequence, parameters addressed in GoT.cpp
if N, add one to whiteWalkerPasses
if whiteWalkerPasses == 5, kill the player
if Y, call Game_is_winter_coming()
*/
void Game::Game_is_winter_coming() {
    string whiteWalkerChoice;
    cout << "The White Walkers are approaching..." << endl;
    cout << "Would you like to battle them now? (Y/N)" << endl;
    cin >> whiteWalkerChoice;
    while(whiteWalkerChoice != "Y" && whiteWalkerChoice != "y" && whiteWalkerChoice != "N" && whiteWalkerChoice != "n") //user error
    {
        cout << "Make a decision... The White Walkers will not wait long." << endl;
        cin >> whiteWalkerChoice;
    }
    if(whiteWalkerChoice == "N" || whiteWalkerChoice == "n" && whiteWalkerPasses < 4) //if no
    {
        cout << "You avoid the White Walkers for now." << endl;
        cout << "But the White Walkers wait for nobody..." << endl;
        cout << endl;
        whiteWalkerPasses++; //number of passes
    }
    else if(whiteWalkerChoice == "N" || whiteWalkerChoice == "n" && whiteWalkerPasses == 4) //if says no 5 times
    {
        cout << "You have run for too long." << endl;
        cout << endl;
        heroes[Game_returnHeroIndex(Game_get_hero_controlled_by_player())].Hero_set_death(true);
        return;
    }
    else if(whiteWalkerChoice == "Y" || whiteWalkerChoice == "y")
    {
        Game_whiteWalkerBattle(); //start battle
    }
} //initialize white walker sequence (would you like to battle?)

/* White walker battle
display appropriate messages
calculate power score
return random integer
if integer > power score, lose round
if integer < power score, win round
if if lose 3 rounds, kill player
if win 1 round, win
*/
void Game::Game_whiteWalkerBattle() {
    cout << "You will now battle the White Walkers." << endl;
    int rounds = 0;
    int warriorsPower = 0;
    int heroesPower = (Game_getCitiesControlled(Game_returnHeroIndex(Game_get_hero_controlled_by_player())) + 1) + (Game_get_hero_controlled_by_player().Hero_getInfluence() / 4);
    double powerScore = 0; //calculate warrior and hero power indivisually
    if(Game_get_hero_controlled_by_player().Hero_has_dragonglass_in_party() == true)
    {
        powerScore = powerScore + 10000; //add for dragonglass
    }
    for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
    {
        int strength = Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getStrength();
        int morale = Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getMorale();
        warriorsPower = warriorsPower + (strength*(morale/50)); //get warrior power
    }
    powerScore = warriorsPower + heroesPower;
    powerScore = powerScore * -1;
    double probability = 1 - (exp(powerScore/30000)); //probability equation
    probability = probability * 100000; //find probability number
    while(turns > 3)
    {
        cout << "Round " << rounds + 1 << ": "; //round outcomes
        double decision = rand() % 10000 + 1;
        if(decision > probability && rounds < 2) //if loss
        {
            cout << "Defeated." << endl;
            rounds++;
        }
        else if(decision > probability && rounds == 2) //if ;pst all
        {
            cout << "Defeated." << endl;
            heroes[Game_returnHeroIndex(Game_get_hero_controlled_by_player())].Hero_set_death(true);
            rounds++;
            return;
        }
        else if(probability > decision)
        {
            cout << "Victorious!" << endl; //if victory
            victorious = true;
            return;
        }
    }
} //white walker battle (probability, 3 rounds)

/* recieve index for hero to check
Search map for cities
if tile = city, check if hero_controlled_by = heroes[index]
if true, add one to number of cities controlled
return number of cities controlled
*/
int Game::Game_getCitiesControlled(int index) {
    int cities = 0;
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            if(Game_map.Map_getTile(i,j).Tile_get_hero_controlled_by().Hero_getName() == heroes[index].Hero_getName()) //if control tile
            {
                if(Game_map.Map_getTile(i,j).Tile_getType() == 3) //if city
                {
                    cities++; //add one
                }
            }
        }
    }
    return cities;
} //return number of cities controlled by player at index

void Game::Game_winnerDisplay() {
    cout << endl;
    cout << "You have conquered Westeros, defeated the White Walkers, and won the Game of Thrones!" << endl;
    cout << endl;
    cout << "There is only one thing we say to death: Not today." << endl;
    cout << endl;
    cout << "Thanks for playing..." << endl;
} //display to winner

bool Game::Game_get_is_victorious() {
    return victorious;
} //set "is victorious"

/* Create a new array the size of the heroes vector
transfer heroes to array
use sorting algorithm to sort by number of points
allocate spacing so it is always aligned, and print top 5 scorers
write to resultsGOT.txt the scoring associated with the user only
*/
void Game::Game_scoreDisplay() {
    Hero arr[Game_getNumHeroes()]; //sorting algoritgm
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        arr[i] = heroes[i]; //temporary array
    }
    Hero hold[1]; //hold array for swapping
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        for(int j = 0; j < Game_getNumHeroes(); j++)
        {
            if(arr[j].Hero_getScore() > arr[j+1].Hero_getScore())
            {
                hold[0] = arr[j+1]; //switch
                arr[j+1] = arr[j];
                arr[j] = hold[0];
            }
        }
    }
    ofstream myfile; //write to file
    myfile.open ("resultsGOT.txt", fstream::app);
    cout << "--------------------------------" << endl;
    for(int k = Game_getNumHeroes()-1; k > Game_getNumHeroes()-6; k--)
    {
        if(arr[k].Hero_getName() == Game_get_hero_controlled_by_player().Hero_getName())
        {
            cout << playerName;
            myfile << playerName;
            for(int i = playerName.length(); i < 9; i++) //organizing spaces
            {
                cout << " ";
                myfile << " ";
            }
            cout << arr[k].Hero_getName();
            myfile << arr[k].Hero_getName();
            for(int i = arr[k].Hero_getName().length(); i < 20; i++) //organizing spaces
            {
                cout << " ";
                myfile << " ";
            }
            cout << arr[k].Hero_getScore() << endl;
            myfile << arr[k].Hero_getScore() << endl;
        }
        else
        {
            cout << "CPU"; //computer name
            for(int i = 3; i < 9; i++)
            {
                cout << " ";
            }
            cout << arr[k].Hero_getName();
            for(int i = arr[k].Hero_getName().length(); i < 20; i++)
            {
                cout << " ";
            }
            cout << arr[k].Hero_getScore() << endl;
        }
    }
    cout << "--------------------------------" << endl;
    myfile.close();
} //sorting algorithm, print scoreboard, write to file

/* return a random number between 1 and 10
if less than or equal to 3, return number between 1 and 4
each number between 1 and 4 corresponds to a random turn event
print appropriate messages and adjust statistics based on event
*/
void Game::Game_randomEvents() {
    int probability = rand() % 10 + 1; //probability of a random event
    if(probability <= 3)
    {
        int eventSelection = rand() % 4 + 1; //selecting event
        {
            if(eventSelection == 1)
            {
                cout << "Drought: There has been no rain in days and the army has very little food left." << endl;
                for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                { //set strength if can
                    if(Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getStrength() > 10)
                    {
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorStrength(i, Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getStrength() - 10);
                    }
                    else
                    { //if less than 10, = 0
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorStrength(i, 0);
                    }
                    if(Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getMorale() > 10)
                    { //set morale
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorMorale(i, Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getMorale() - 10);
                    }
                    else
                    { // ifles than 10, = 0
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorMorale(i, 0);
                    }
                }
            }
            if(eventSelection == 2)
            {
                cout << "Deserters: This campaign is taking a very long time and the soldiers are tired and sad. Some decide to leave." << endl;
                for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                {
                    if(Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getLoyalty() > 10)
                    { //set loyalty
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorLoyalty(i, Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getLoyalty() - 10);
                    }
                    else
                    { //if cant, set to 0
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorLoyalty(i, 0);
                    }
                    if(Game_get_hero_controlled_by_player().Hero_getArmySize() > 10)
                    { //set army size
                        Game_setArmySize(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getArmySize() - 10);
                    }
                    else
                    { //if cant, set to 0
                        Game_setArmySize(Game_returnHero_controlled_by_playerindex(), 0);
                    }
                }
            }
            if(eventSelection == 3)
            { //set money * 2
                cout << "Jackpot: your heroic cause has won the hearts of many noble and wealthy benefactors! They generously donate funds to your cause." << endl;
                Game_setMoney(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getMoney() * 2);

            }
            if(eventSelection == 4)
            {
                cout << "Kindness: you decide to offer shelter to some refugees." << endl;
                Game_setArmySize(Game_returnHero_controlled_by_playerindex(), Game_get_hero_controlled_by_player().Hero_getArmySize() + 10);
                for(int i = 0; i < Game_get_hero_controlled_by_player().Hero_getNumWarriors(); i++)
                { //set warrior stats
                    if(Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getLoyalty() <= 90)
                    {
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorLoyalty(i, Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getLoyalty() + 10);
                    }
                    else
                    {
                        heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorLoyalty(i, 100);
                    } //if more than 90, set to 100
                    heroes[Game_returnHero_controlled_by_playerindex()].Hero_setWarriorLoyalty(i, Game_get_hero_controlled_by_player().Hero_getWarriors(i).Warrior_getLoyalty() + 10);
                }
            }
        }
    }
    else
    {
        return;
    }
} //random turn events

/* int index of hero
traverse map, if hero_controlled_by = heroes[index], add one to number of tiles controlled
return number of tiles controlled
*/
int Game::Game_getTilesControlled(int index) {
    int tiles = 0;
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            if(Game_map.Map_getTile(i,j).Tile_get_hero_controlled_by().Hero_getName() == heroes[index].Hero_getName())
            {
                tiles++;
            }
        }
    }
    return tiles;
} //return number of tiles controlled by player at index

/*Traverse heroes array
if heroes[i] != hero controlled by player, move that hero
check if hero can move (water with no ship, end of map, etc.)
if it can, move that hero
*/
void Game::Game_moveOtherHeroes() {
    for(int i = 0; i < Game_getNumHeroes(); i++) //for each hero
    {
        int direction = rand() % 4 + 1; //random direction
        if(i != Game_returnHero_controlled_by_playerindex())
        {
            while(Game_heroCanMoveInDirection(i, direction) == false) //if cant
            {
                direction = rand() % 4 + 1; //new direction
            }
            if(Game_heroCanMoveInDirection(i, direction) == true)
            {
                Game_movePlayer(i, direction); //if can, move
            }
            if(Game_map.Map_getTile(heroes[i].Hero_getLocation_Row(), heroes[i].Hero_getLocation_Column()).Tile_get_has_dragonglass() == true)
            {
                Game_map.Map_setDragonglass(heroes[i].Hero_getLocation_Row(), heroes[i].Hero_getLocation_Column(), false); //if finds dragonglass, remove it
            }
        }
    }
} //function to move all non-player heroes

/* Traverse warriors array
if warrior != free, find hero it belongs to
set location to the location of its hero
if warrior is free, randomize row and column coordinates
check if other hero/warrior present. if no, put warrior at that spot. if yes, randomize again
*/
void Game::Game_setWarriorLocations() {
    for(int i = 0; i < Game_getNumWarriors(); i++)
    {
        if(warriors[i].Warrior_get_is_free() == true && warriors[i].Warrior_get_has_ship() == false) //for free alive warriors
        {
            int row = rand() % 24 + 1; //random locations
            int column = rand() % 15 + 1;
            for(int j = 0; j < Game_getNumWarriors(); j++)
            {
                for(int k = 0; k < Game_getNumHeroes(); k++)
                {
                    while(warriors[j].Warrior_getLocationColumn() == column && warriors[j].Warrior_getLocationRow() == row || heroes[k].Hero_getLocation_Column() == column && heroes[k].Hero_getLocation_Row() || Game_map.Map_getTile(row,column).Tile_getType() != 2)
                    { //if cant place there
                        row = rand() % 24 + 1;
                        column = rand() % 15 + 1;
                    }
                }
            }
            warriors[i].Warrior_setLocationRow(row); //set location
            warriors[i].Warrior_setLocationColumn(column);
        }
        if(warriors[i].Warrior_get_is_free() == true && warriors[i].Warrior_get_has_ship() == true) //if warrior hsa ship
        {
            int row = rand() % 24 + 1;
            int column = rand() % 15 + 1;
            for(int j = 0; j < Game_getNumWarriors(); j++)
            {
                for(int k = 0; k < Game_getNumHeroes(); k++)
                {
                    while(warriors[j].Warrior_getLocationColumn() == column && warriors[j].Warrior_getLocationRow() == row || heroes[k].Hero_getLocation_Column() == column && heroes[k].Hero_getLocation_Row() || Game_map.Map_getTile(row,column).Tile_getType() != 1)
                    { //if can't place ther,e find new location
                        row = rand() % 24 + 1;
                        column = rand() % 15 + 1;
                    }
                }
            }
            warriors[i].Warrior_setLocationRow(row); //set location
            warriors[i].Warrior_setLocationColumn(column);
        }
        if(warriors[i].Warrior_get_is_free() == false) //if not free, put with hero
        {
            for(int j = 0; j < Game_getNumHeroes(); j++)
            {
                for(int k = 0; k < heroes[j].Hero_getNumWarriors(); k++)
                {
                    if(heroes[j].Hero_getWarriors(k).Warrior_getName() == warriors[i].Warrior_getName())
                    {
                        warriors[i].Warrior_setLocationColumn(heroes[j].Hero_getLocation_Column());
                        warriors[i].Warrior_setLocationRow(heroes[j].Hero_getLocation_Row());
                    }
                }
            }
        }
    }
} //function to initialize location of all warriors

/* Traverse array of heroes
if hero is within range of a warrior and the warrior is free and the warriors array is not full, then that hero acquires that warrior
display appropriate message
*/
void Game::Game_acquireWarriors() {
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        if(Game_is_in_vicinity_warrior(heroes[i]) == true && heroes[i].Hero_getNumWarriors() < 4 && warriors[Game_getNearestWarrior(heroes[i])].Warrior_get_is_free() == true)
        {
            heroes[i].Hero_setWarriors(warriors[Game_getNearestWarrior(heroes[i])], heroes[i].Hero_getNumWarriors()); //set warrior
            warriors[Game_getNearestWarrior(heroes[i])].Warrior_set_is_free(false); //isn't free
            if(i == Game_returnHero_controlled_by_playerindex())
            {
                cout << "You have acquired " << heroes[i].Hero_getWarriors(heroes[i].Hero_getNumWarriors() - 1).Warrior_getName() << "!" << endl;
                cout << endl; //acquisition message
            }
        }
    }
} //function to acquire warriors if within range

/* Traverse heroes array
if heroes[i] is in range of another hero, check conditions
if both heroes have 0 warriors, warrior with largest army wins
if one hero has 1+ warrior(s) and the other doesn't, that hero wins
if both heroes have warriors, a random warrior is selected to represent
calculate probability, probability decides winner
*/
void Game::Game_resolveCPUEncounters() {
    for(int i = 0; i < Game_getNumHeroes(); i++)
    {
        if(Game_is_in_vicinity_hero(heroes[i]) == true && i != Game_returnHero_controlled_by_playerindex() && heroes[i].Hero_get_death() == false)
        {
            int a;
            for(int j = 0; j < Game_getNumHeroes(); j++)
            {
                if(Game_getNearesthero(heroes[i]).Hero_getName() == heroes[j].Hero_getName() && j != Game_returnHero_controlled_by_playerindex())
                {
                    a = j; //other encountered hero index
                }
            }
            if(heroes[a].Hero_getNumWarriors() == 0 && heroes[i].Hero_getNumWarriors() == 0 && a != Game_returnHero_controlled_by_playerindex() && i != Game_returnHero_controlled_by_playerindex()  && a != i) //if neither have warriors
            {
                if(heroes[a].Hero_getArmySize() > heroes[i].Hero_getArmySize())
                {
                    cout << endl;
                    cout << heroes[i].Hero_getName() << " has retired." << endl;
                    heroes[i].Hero_set_death(true);
                    return;
                }
                else if(heroes[a].Hero_getArmySize() < heroes[i].Hero_getArmySize()) //if one has warrior
                {
                    cout << endl;
                    cout << heroes[a].Hero_getName() << " has retired." << endl;
                    heroes[a].Hero_set_death(true);
                    return;
                }
                else
                {
                    cout << endl;
                    cout << heroes[a].Hero_getName() << " has retired." << endl; //if other has warrior
                    heroes[a].Hero_set_death(true);
                    return;
                }
            }
            else if(heroes[i].Hero_getNumWarriors() == 0 && heroes[a].Hero_getNumWarriors() > 0 && a != Game_returnHero_controlled_by_playerindex() && i != Game_returnHero_controlled_by_playerindex() && a != i) //if one has warrior
            {
                cout << endl;
                cout << heroes[i].Hero_getName() << " has retired." << endl;
                heroes[i].Hero_set_death(true);
                return;
            }
            else if(heroes[a].Hero_getNumWarriors() == 0 && heroes[i].Hero_getNumWarriors() > 0 && a != Game_returnHero_controlled_by_playerindex() && i != Game_returnHero_controlled_by_playerindex() && a != i) //if other has warrior
            {
                cout << endl;
                cout << heroes[a].Hero_getName() << " has retired." << endl;
                heroes[i].Hero_set_death(true);
                return;
            }
            else if(heroes[a].Hero_getNumWarriors() > 0 && heroes[i].Hero_getNumWarriors() > 0 && a != Game_returnHero_controlled_by_playerindex() && i != Game_returnHero_controlled_by_playerindex() && a != i) //if both have heroes
            {
                int hero1 = rand() % heroes[i].Hero_getNumWarriors() + 1; //random hero representation
                int hero2 = rand() % heroes[a].Hero_getNumWarriors() + 1;
                if((heroes[i].Hero_getWarriors(hero1).Warrior_getStrength() * heroes[i].Hero_getArmySize()) > (heroes[a].Hero_getWarriors(hero1).Warrior_getStrength() * heroes[a].Hero_getArmySize()))
                {
                    cout << endl;
                    cout << heroes[a].Hero_getName() << " has retired." << endl;
                    heroes[a].Hero_set_death(true);
                    return;
                }
                else if((heroes[i].Hero_getWarriors(hero1).Warrior_getStrength() * heroes[i].Hero_getArmySize()) < (heroes[a].Hero_getWarriors(hero1).Warrior_getStrength() * heroes[a].Hero_getArmySize()))
                {
                    cout << endl;
                    cout << heroes[i].Hero_getName() << " has retired." << endl;
                    heroes[i].Hero_set_death(true);
                    return;
                }
                else if((heroes[i].Hero_getWarriors(hero1).Warrior_getStrength() * heroes[i].Hero_getArmySize()) == (heroes[a].Hero_getWarriors(hero1).Warrior_getStrength() * heroes[a].Hero_getArmySize()))
                {
                    cout << endl;
                    cout << heroes[a].Hero_getName() << " has retired." << endl;
                    heroes[a].Hero_set_death(true);
                    return;
                }
            }

        }
    }
    return;
} //function to resolve all CPU encounters
