#ifndef CHARACTER_H_
#define CHARACTER_H_
//#include "World.h"
#include "Trap.h"
#include "InventoryArrayTemp.tci"

#include <string>
using namespace std;


class Character {
private:
    string description;
    InventoryTemplate<Trap> trapInventory;
public:
    //Character();
    Character(string description = "player");
    void addTrap(Trap* trap);
    Trap* getTrap(string name);
    Trap* getTrap(int n);
    int getTrapArrLength();
    //Trap getInventorySlot(int pos);
    string printTraps();
};

#endif /*CHARACTER_H_*/
