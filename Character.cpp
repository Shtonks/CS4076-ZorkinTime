#include "Character.h"

//<LUKE><TBD>Anywhere TBD means To Be Deleted

//<LUKE> Implemented intializer list for trap inventory
Character::Character(string description, int inventorySize) : trapInventory(inventorySize), blueprintInv(inventorySize) {
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

//void Character::addBlueprint(Trap* blueprint){
//    trapInventory.add(*trap);
//}

//Trap* Character::getTrap(string name){
//    return trapInventory.get(name);
//}

//void Character::removeTrap(string name){

//    trapInventory.remove(*getTrap(name));
//}


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
