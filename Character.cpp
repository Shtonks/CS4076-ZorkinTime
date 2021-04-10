#include "Character.h"

//<LUKE><TBD>Anywhere TBD means To Be Deleted

//<LUKE> Implemented intializer list for trap inventory
Character::Character(string description) : trapInventory(3) {
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


////CREATE A TEMPLATE CLASS FOR INVENTORY???
//Trap Character::getInventorySlot(int pos){
//    return trapInventory.at(pos);
//}



/*
string Character::longDescription()
{
  string ret = this->description;
  ret += "\n Item list:\n";
  for (vector<Item>::iterator i = .begin(); i != itemsInCharacter.end(); i++)
    ret += "\t"+ (*i).getDescription() + "\n";
  return ret;
}
*/
