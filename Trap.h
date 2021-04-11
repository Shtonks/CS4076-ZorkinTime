#pragma once

#include "Item.h"
#include "Bigbad.h"
#include "Riskfactor.h"
#include <string>
#include <time.h>

#define SLASHING 0
#define PIERCING 1
#define BLUDGEONING 2
#define FIRE 3
#define COLD 4
#define POISON 5
#define NOTHING 6

class Trap : public Item, public RiskFactor {
    private:
        int dmgType;
        int maxDmg;
        int baseDmg;
        int dealtDmg;
    public:
        Trap(const string &name = "", const string &description = "", int timeMod = 0, int dmgType = NOTHING,int baseDmg = 0, int maxDmg = 1);
        string getDmgType();
        int getDmgTypeNum();
        string getDmgType(int typeNum);
        void setDmgType(int dmgtype);
        void setDealtDmg(); //<ISHA> calculates damage dealt between baseDamage - maxDamage
        void setDealtDmg(double factor); //<ISHA> Multiplies Dealt damage by a factor depending on room
        void setMaxDmg(int inc);
        int getDealtDmg();
        int getMaxDmg();
        int getBaseDmg();
        void setVulnerable(int vulnerable);
        void setResistant(int resistant);
        string toString();
        bool operator== (const Trap & rhs) const;   // c1 == c2
};
