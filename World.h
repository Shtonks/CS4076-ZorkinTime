#pragma once

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "Item.h"
#include <iostream>
#include <string>
using namespace std;

class World {
private:
    Parser parser;
    vector<Room*> genRooms; //<LUKE> short for generated rooms
    int numMoves = 100;
    Room *currentRoom;
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void createItems();
    void displayItems();

public:
    World();
    void play();
    string go(string direction);
};