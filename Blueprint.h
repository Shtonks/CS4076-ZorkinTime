#ifndef BLUEPRINT_H
#define BLUEPRINT_H

#include "Trap.h"
#include "Item.h"

class Blueprint : public Item{
private:
    int dmgType;
    int increase;
public:
    Blueprint(const string &name = "", const string &description = "", int timeMod = 0, int dmgType = NOTHING, int increase = 0);
    void enhanceTrap(Trap& t);
    string getDmgType();
    int getIncrease();

};

#endif // BLUEPRINT_H
