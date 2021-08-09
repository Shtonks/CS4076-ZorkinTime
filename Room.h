#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include "Item.h"
#include "Trap.h"
#include "Blueprint.h"

using namespace std;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    void findBonusDmgType(int type);
    string bonusDmgType = "nothing";
    Trap* trapInRoom = nullptr;
    string icon;
    Blueprint* blueprintInRoom = nullptr;


public:
    Room(string description, int dmgType);
    Room(const Room &r);
    ~Room();
	void setExits(Room *north, Room *east, Room *south, Room *west);
    string getDescription();
	Room* nextRoom(string direction);
    inline string getBonusDmgType();
    void placeTrap(Trap& t);
    string getIcon();
    Trap* getTrapInRoom();
    void setTrapInRoom(Trap* t);
    Blueprint* getBlueprintInRoom();
    void setBlueprintInRoom(Blueprint* b);

};

#endif
