#pragma once

#include "Room.h"
#include "Item.h"
#include "Character.h"
#include <iostream>
#include <string>
using namespace std;

class World {
    friend class MainWindow;
    friend class ShopInterface;
private:
    Character player;
    Character shop;
    Room *genRooms[16];
    int numMoves = 100;
    Room* currentRoom;
    Room* shopRoom;
    void createRooms();
    void createItems();
    string currentRoomLabel;
    //void printHelp();
    //void displayItems();

public:
    World();
    void printWelcome();
    bool go(string direction);
    Room* getCurrentRoom();
    void setCurrentRoom(Room* r);
    string getCurrentRoomLabel();
    Room** getGenRooms();
    string getShopRoomLabel();
};
