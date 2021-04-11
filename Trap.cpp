#include "Trap.h"
#include <string>

Trap::Trap(const string &name, const string &description, int timeMod, int dmgType,int baseDmg, int maxDmg) :
    Item(name, description, timeMod)
{
    this->dmgType = dmgType;
    this->baseDmg = baseDmg;
    this->maxDmg = maxDmg;
    setDealtDmg();
}


string Trap::getDmgType(){
    string out;
    switch(dmgType){
    case SLASHING: out = "slashing"; break;
    case PIERCING: out = "piercing"; break;
    case BLUDGEONING: out ="bludgeoning"; break;
    case FIRE: out = "fire"; break;
    case COLD: out = "cold"; break;
    case POISON: out = "poison"; break;
    case NOTHING: out = "nothing special"; break;
    }
    return out;
}

int Trap::getDmgTypeNum(){
    return dmgType;
}

void Trap::setDmgType(int dmgType){
    this->dmgType = dmgType;
}

//Calculates damage dealt between baseDmg - maxDmg
void Trap::setDealtDmg(){
    srand(time(0));
    dealtDmg = rand() % (maxDmg-baseDmg) + baseDmg;
}

void Trap::setDealtDmg(double factor){
    dealtDmg *= factor;
}

int Trap::getDealtDmg(){
    return dealtDmg;
}

void Trap::setMaxDmg(int inc){
    maxDmg += inc;
    setDealtDmg();
}

int Trap::getMaxDmg(){
    return maxDmg;
}

int Trap::getBaseDmg(){
    return baseDmg;
}

void Trap::setVulnerable(int vulnerablility){
    if(dmgType == vulnerablility) vulnerable = true;
    if(vulnerable) dealtDmg *= 2;
}


void Trap::setResistant(int resistance){
    if(dmgType == resistance) resistant = true;
    if(resistant) dealtDmg /= 2;
}
