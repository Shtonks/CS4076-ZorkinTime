#include "Character.h"

//<LUKE><TBD>Anywhere TBD means To Be Deleted
Character::Character(string description) {
	this->description = description;
}

//<LUKE><TBD> Chris originally had pass-by-ref and ptr but I thought they MAY be inefficient
//and I also couldn't get them working

//<LUKE>copying in whole object with pass-by-value since will mean all items are now contiguous in
//memory, quicker to access
void Character::addItem(Item item){
    itemsInCharacter.push_back(item);
}

/*
void Character::placeTrap(){
    //check if trap in room
    //check if room offers bonuses to trap
    //delete item
}
*/

string Character::longDescription()
{
  string ret = this->description;
  ret += "\n Item list:\n";
  for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
    ret += "\t"+ (*i).getDescription() + "\n";
  return ret;
}



