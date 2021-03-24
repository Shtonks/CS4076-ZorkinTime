#pragma once

#include "Item.h"
#include <string>

class Trap : public Item {
    private:
        string dmgType;
        int maxDmg;
        int baseDmg;
        int dealtDmg;
        bool effective;
    public:
        Trap(string name, string description, int timeMod, string dmgType,int baseDmg, int maxDmg, bool effective);
        string getDmgType();
        void setDmgType(string dmgtype);
        void setDealtDmg(); //calculates damage dealt between 1 - maxDamage
        int getDealtDmg();
        void setEffective(bool e);
        bool isEffective();
};
