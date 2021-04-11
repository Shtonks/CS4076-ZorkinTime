#include "Room.h"


Room::Room(string description, int dmgType) {
    this->description = description;
    findBonusDmgType(dmgType);
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
    return description + "(Bonus damage type is " + bonusDmgType + ")";
}

//<LUKE> Tried to use a switch statement here, couldn't get working
//<ISHA> Got it :)
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
	map<string, Room*>::iterator next = exits.find(direction); //returns an iterator for the "pair"
	if (next == exits.end())
		return NULL; // if exits.end() was returned, there's no room in that direction.
	return next->second; // If there is a room, remove the "second" (Room*)
				// part of the "pair" (<string, Room*>) and return it.
}


void Room::placeTrap(Trap& t){
    if(trapInRoom == nullptr){
        return;
    }
    if(t.getDmgType().compare(bonusDmgType)){
        //<LUKE> Only temp. May need to be balanced
        //Future luke fix
        t.setDealtDmg(1.5);
    }
    trapInRoom = &t;
}

Trap* Room::getTrapInRoom(){
    return trapInRoom;
}


string Room::getIcon(){
    return icon;
}

void Room::setTrapInRoom(Trap* t){
    trapInRoom = t;
}


