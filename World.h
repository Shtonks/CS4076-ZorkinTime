#pragma once

#include "Room.h"
#include "Item.h"
#include <iostream>
#include <string>
using namespace std;

class World {
private:
    Room *genRooms[16];
    int numMoves = 100;
    Room *currentRoom;
    void createRooms();
    void createItems();
    void printWelcome();
    //void printHelp();
    //void displayItems();

public:
    World();
    void play();
    string go(string direction);
};
