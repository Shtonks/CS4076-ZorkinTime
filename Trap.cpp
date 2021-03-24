#include "Trap.h"
#include <string>

Trap::Trap(string name, string description, string dmgType, int maxDmg, int timeMod, bool effective){
    Item(name,description,timeMod);
    this->dmgType = dmgType;
    this->maxDmg = maxDmg;
    this->effective = effective;
    setDealtDmg();
}

string Trap::getDmgType(){
    return dmgType;
}

void Trap::setDmgType(string dmgtype){
    this->dmgType = dmgtype;
}

int Trap::setDealtDmg(){
    dealtDmg = rand() % maxDmg + 1;
    if(effective) dealtDmg *= 2;
    return dealtDmg;
} //calculates damage dealt between 1 - maxDamage

void Trap::setEffective(bool effective){
    this->effective = effective;
}

bool Trap::isEffective(){
    return effective;
}

