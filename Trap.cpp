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

void Trap::setDmgType(int dmgType){
    this->dmgType = dmgType;
}

void Trap::setDealtDmg(){
    dealtDmg = 50;
    //<LUKE> Temp comment out as was segmnet faulting here
    //dealtDmg = rand() % (maxDmg-baseDmg) + baseDmg;
} //calculates damage dealt between baseDmg - maxDmg

void Trap::setDealtDmg(double factor){
    dealtDmg *= factor;
}

int Trap::getDealtDmg(){
    return dealtDmg;
}

void Trap::setVulnerable(bool vulnerable){
    this->vulnerable = vulnerable;
    if(vulnerable) dealtDmg *= 2;
}

bool Trap::isVulnerable(){
    return vulnerable;
}

void Trap::setResistant(bool resistant){
    this->resistant = resistant;
    if(resistant) dealtDmg /= 2;
}

bool Trap::isResistant(){
    return resistant;
}

string Trap::toString(){
    return "Name: " + getName() +
           "\nAmount: " + to_string(getAmount()) +
           "\nTime Taken: " + to_string(getTimeMod()) +
           "\n"+ to_string(baseDmg)+ "-" + to_string(maxDmg) + " " + getDmgType() + "damage" +
           "\nDescription: " + getDescription();
}
