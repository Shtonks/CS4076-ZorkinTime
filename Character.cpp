#include "Character.h"

//<LUKE> Implemented intializer list for trap inventory
Character::Character(string description, int trapInvSize, int blueprintInvSize)
    : trapInventory(trapInvSize), blueprintInv(blueprintInvSize) {
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

void Character::removeTrap(string name){

    trapInventory.remove(*getTrap(name));
}

void Character::addBlueprint(Blueprint* blueprint){
    blueprintInv.add(*blueprint);
}

Blueprint* Character::getBlueprint(string name){
    return blueprintInv.get(name);
}

Blueprint* Character::getBlueprint(int n){
    return &blueprintInv[n];
}

void Character::removeBlueprint(string name){

    blueprintInv.remove(*getBlueprint(name));
}

int Character::getBlueprintArrLength(){
    return trapInventory.getLength();
}

int Character::getTrapArrLength(){
    return trapInventory.getLength();
}
