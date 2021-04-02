#include "Room.h"


Room::Room(string description) {
	this->description = description;
    findBonusDmgType(description);
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
void Room::findBonusDmgType(string type){
    if(type.find("Sword") != string::npos){
        bonusDmgType = "slashing";
        //this needs to be replicated all way down
        icon = "overlay-slash.png";
        return;
    }
    else if(type.find("Spear") != string::npos){
        bonusDmgType = "piercing";
        icon = "overlay-pierce.png";
        return;
    }
    else if(type.find("Mace") != string::npos){
        bonusDmgType = "bludgeoning";
        icon = "overlay-bludgeon.png";
        return;
    }
    else if(type.find("Flame") != string::npos){
        bonusDmgType = "fire";
        icon = "overlay-fire.png";
        return;
    }
    else if(type.find("Frost") != string::npos){
        bonusDmgType = "cold";
        icon = "overlay-ice.png";
        return;
    }
    else if(type.find("Snake") != string::npos){
        bonusDmgType = "poison";
        icon = "overlay-poison.png";
        return;
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

string Room::getIcon(){
    return icon;
}

void Room::setIsPlayerInRoom(bool n){
    isPlayerInRoom = n;
}

bool Room::getIsPlayerInRoom(){
    return isPlayerInRoom;
}

/*
<LUKE> maybe maybe maybe
void Room::addItem(Item *inItem) {
    //cout <<endl;
    //cout << "Just added" + inItem->getLongDescription();
    itemsInRoom.push_back(*inItem);
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x].getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x].getShortDescription());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}
*/

