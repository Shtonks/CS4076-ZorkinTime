#include "Room.h"


Room::Room(string description, int dmgType) {
    this->description = description;
    findBonusDmgType(dmgType);
}
//Copy Constructor
Room::Room(const Room &r){
    trapInRoom = new Trap;
    *trapInRoom = *r.trapInRoom;
    blueprintInRoom = new Blueprint;
    *blueprintInRoom = *r.blueprintInRoom;
}

Room::~Room(){
    delete trapInRoom;
    delete blueprintInRoom;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
	if (north != NULL)
        exits["North"] = north;
	if (east != NULL)
        exits["East"] = east;
	if (south != NULL)
        exits["South"] = south;
	if (west != NULL)
        exits["West"] = west;
}


string Room::getDescription() {
    return description + " (Bonus damage type is " + bonusDmgType + ")";
}

void Room::findBonusDmgType(int type){
    switch (type){
        case SLASHING: bonusDmgType = "slashing"; icon = "overlay-slash.png"; break;
        case PIERCING: bonusDmgType = "piercing"; icon = "overlay-pierce.png"; break;
        case BLUDGEONING: bonusDmgType = "bludgeoning"; icon = "overlay-bludgeon.png"; break;
        case FIRE: bonusDmgType = "fire"; icon = "overlay-fire.png"; break;
        case COLD: bonusDmgType = "cold"; icon = "overlay-ice.png"; break;
        case POISON: bonusDmgType = "poison"; icon = "overlay-poison.png"; break;
    }
}

inline string Room::getBonusDmgType(){
    return bonusDmgType;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction);
	if (next == exits.end())
        return NULL;
    return next->second;
}


void Room::placeTrap(Trap& t){
    if(trapInRoom == nullptr){
        return;
    }
    if(t.getDmgType().compare(bonusDmgType)){
        t.setDealtDmg(1.5);
    }
    trapInRoom = &t;
}

Trap* Room::getTrapInRoom(){
    return trapInRoom;
}

void Room::setTrapInRoom(Trap* t){
    trapInRoom = t;
}

Blueprint* Room::getBlueprintInRoom(){
    return blueprintInRoom;
}

void Room::setBlueprintInRoom(Blueprint* b){
    blueprintInRoom = b;
}


string Room::getIcon(){
    return icon;
}




