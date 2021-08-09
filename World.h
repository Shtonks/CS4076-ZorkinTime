#pragma once

#define INTRO "Welcome to the Underground"

#include "Room.h"
#include "Item.h"
#include "Character.h"
#include "BigBad.h"
#include <iostream>
#include <string>

using namespace std;
namespace globals{};

class World {
    friend class MainWindow;
    friend class ShopInterface;
private:
    BigBad bb;
    Character player;
    Character shop;
    Room *genRooms[16];
    int numMoves = 150;
    const int numOfRooms = 16;
    Room* currentRoom;
    Room* shopRoom;
    void createRooms();
    void createItems();
    string currentRoomLabel;

public:
    struct roomAttbs;
    World();
    ~World();
    string printWelcome();
    bool go(string direction);
    Room* getCurrentRoom();
    void setCurrentRoom(Room* r);
    string getCurrentRoomLabel();
    Room** getGenRooms();
    string getShopRoomLabel();
    int getNumMoves();
    void setNumMoves(int n);
    int neverToBeUsedGlobalVar = 0;
};
