#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include "Item.h"
#include "Trap.h"

using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;
    void findBonusDmgType(string type);
    string bonusDmgType = "nothing";
    Trap *trapInRoom = nullptr;
    string icon;

public:
    Room(string description);
	void setExits(Room *north, Room *east, Room *south, Room *west);
    string getDescription();
	Room* nextRoom(string direction);
    //void addItem(Item *inItem);
    //string displayItem();
    //int isItemInRoom(string inString);
    //void removeItemFromRoom(int location);
    inline string getBonusDmgType();
    void placeTrap(Trap* t);
    string getIcon();
};

#endif
