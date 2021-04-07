#pragma once

#include "Item.h"
#include <string>

class Trap : public Item {
    private:
        string dmgType;
        int maxDmg;
        int baseDmg;
        int dealtDmg;
        bool vulnerable;
        bool resistant;
    public:
        Trap(const string &name = "", const string &description = "", int timeMod = 0, const string &dmgType = "",int baseDmg = 0, int maxDmg = 0);
        string getDmgType();
        void setDmgType(string dmgtype);
        void setDealtDmg(); //<ISHA> calculates damage dealt between baseDamage - maxDamage
        void setDealtDmg(double factor); //<ISHA> Multiplies Dealt damage by a factor depending on room
        int getDealtDmg();
        void setVulnerable(bool vulnerable);
        bool isVulnerable();
        void setResistant(bool resistant);
        bool isResistant();
        string toString();
};
