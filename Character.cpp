#include "Character.h"

//<LUKE><TBD>Anywhere TBD means To Be Deleted

//<LUKE> Implemented intializer list for trap inventory
Character::Character(string description) : trapInventory(10) {
	this->description = description;
}

void Character::addTrap(Trap* trap){
    trapInventory.add(*trap);
}

Trap* Character::getTrap(string name){
    return trapInventory.get(name);
}

Trap* Character::getTrap(int n){
    return &trapInventory[n];
}

int Character::getTrapArrLength(){
    return trapInventory.getLength();
}


string Character::printTraps(){
    string all = "";
    for(int i = 0; i < trapInventory.getLength(); i++){
        all = all + "   " + trapInventory[i].getName() + "///";
    }
    return all;
}
