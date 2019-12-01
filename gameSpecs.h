/*
 * This file holds global constants, data types, and their associated helper
 * functions for the game of battleship.
 */
#ifndef ___GAME_SPECS___
#define ___GAME_SPECS___

#include <string>
using namespace std;

// ENUM to hold shipe placement and hit or miss info.
enum Tile
{
    WATER, 
    AIRCRAFT_CARRIER,
    BATTLESHIP,
    SUBMARINE,
    DESTROYER,
    PATROL_BOAT,
    MISS,
    AIRCRAFT_CARRIER_HIT,
    BATTLESHIP_HIT,
    SUBMARINE_HIT,
    DESTROYER_HIT,
    PATROL_BOAT_HIT
};

const int numOfPlayableBoats = 5;
const int BOARD_LENGTH = 10;

const int SHIP_SIZE[numOfPlayableBoats + 1] { 0, 5, 4, 3, 3, 2 };

string shipToString(Tile input);

char tileToSymbol(Tile input);

string shipToString(Tile input)
{
    switch(input)
    {
        case WATER:
            return "Water";
        case AIRCRAFT_CARRIER:
            return "Aircraft Carrier";
        case BATTLESHIP:
            return "Battleship";
        case SUBMARINE:
            return "Submarine";
        case DESTROYER:
            return "Destroyer";
        case PATROL_BOAT:
            return "Patrol Boat";
        case MISS:
            return "Miss";
        case AIRCRAFT_CARRIER_HIT:
            return "Aircraft Carrier";
        case BATTLESHIP_HIT:
            return "Battleship";
        case SUBMARINE_HIT:
            return "Submarine";
        case DESTROYER_HIT:
            return "Destroyer";
        case PATROL_BOAT_HIT:
            return "Patrol Boat";
        default: 
            return "Error";
    }
}

char tileToSymbol(Tile input)
{
    switch(input)
    {
        case WATER:
            return '.';
        case AIRCRAFT_CARRIER:
            return 'A';
        case BATTLESHIP:
            return 'B';
        case SUBMARINE:
            return 'S';
        case DESTROYER:
            return 'D';
        case PATROL_BOAT:
            return 'P';
        case MISS:
            return '~';
        case AIRCRAFT_CARRIER_HIT:
            return 'a';
        case BATTLESHIP_HIT:
            return 'b';
        case SUBMARINE_HIT:
            return 's';
        case DESTROYER_HIT:
            return 'd';
        case PATROL_BOAT_HIT:
            return 'p';
        default: 
            return ' ';
    }
}
// Put new code here.


#endif