#pragma once

#include "Room.h"
#include "Item.h"
#include "Character.h"
#include <iostream>
#include <string>
using namespace std;
namespace globals{};

class World {
    friend class MainWindow;
private:
    Character player;
    Character shop;
    Room *genRooms[16];
    int numMoves = 100;
    Room *currentRoom;
    void createRooms();
    void createItems();
    string currentRoomLabel;
    //void printHelp();
    //void displayItems();

public:
//    template<class Item> Item ItemLonger(Item *i1, Item *i2);
    struct roomAttbs;
    World();
    void printWelcome();
    bool go(string direction);
    Room* getCurrentRoom();
    void setCurrentRoom(Room* r);
    string getCurrentRoomLabel();
    Room** getGenRooms();
};
