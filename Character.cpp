#include "Character.h"

//<LUKE><TBD>Anywhere TBD means To Be Deleted

//<LUKE> Implemented intializer list for trap inventory
//OLD:  Character::Character(string description) : trapInventory(10) {
Character::Character(string description){
	this->description = description;
}

////CREATE A TEMPLATE CLASS FOR INVENTORY???
//Trap Character::getInventorySlot(int pos){
//    return trapInventory.at(pos);
//}

//void Character::addTrap(Trap &trap){
//    trapInventory.add(trap);
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
