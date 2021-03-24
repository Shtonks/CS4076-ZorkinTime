#pragma once

#include "Item.h"
#include <string>

class Trap : public Item {
    private:
        string dmgType;
        int maxDmg;
        int dealtDmg;
        bool effective;
    public:
        Trap(string name, string description, string dmgType, int maxDmg, int timeMod, bool effective);
        string getDmgType();
        void setDmgType(string dmgtype);
        int setDealtDmg(); //calculates damage dealt between 1 - maxDamage
        void setEffective(bool e);
        bool isEffective();
};
