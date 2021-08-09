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
    Character(string description, int trapInvSize, int blueprintInvSize);
    void addTrap(Trap* trap);
    Trap* getTrap(string name);
    Trap* getTrap(int n);
    void removeTrap(string name);
    int getTrapArrLength();
    void addBlueprint(Blueprint* blueprint);
    Blueprint* getBlueprint(string name);
    Blueprint* getBlueprint(int n);
    void removeBlueprint(string name);
    int getBlueprintArrLength();
};

#endif /*CHARACTER_H_*/
