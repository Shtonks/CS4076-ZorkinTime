#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Trap.h"
#include "Blueprint.h"
#include "InventoryArrayTemp.tci"

#include <string>
using namespace std;


class Character {
private:
    string description;
    InventoryTemplate<Trap> trapInventory;
    InventoryTemplate<Blueprint> blueprintInv;
public:
    //Character();
    Character(string description = "player", int inventorySize = 10);
    void addTrap(Trap* trap);
    Trap* getTrap(string name);
    Trap* getTrap(int n);
    void removeTrap(string name);
    int getTrapArrLength();
    //Trap getInventorySlot(int pos);
    string printTraps();
};

#endif /*CHARACTER_H_*/
