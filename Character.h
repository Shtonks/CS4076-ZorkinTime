#ifndef CHARACTER_H_
#define CHARACTER_H_
//#include "World.h"
#include "Trap.h"
#include "InventoryTemplate.tci"

#include <string>
using namespace std;


class Character {
private:
    string description;
    //Inventory<Trap> trapInventory;
public:
    //Character();
    Character(string description = "player");
    void addTrap(Trap &trap);
    Trap getInventorySlot(int pos);
};

#endif /*CHARACTER_H_*/
