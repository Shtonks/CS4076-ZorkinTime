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

void Trap::setDealtDmg(){
    dealtDmg = rand() % maxDmg + 1;
} //calculates damage dealt between 1 - maxDamage

int Trap::getDealtDmg(){
    return dealtDmg;
}

void Trap::setEffective(bool effective){
    this->effective = effective;
    if(effective) dealtDmg *= 2;
}

bool Trap::isEffective(){
    return effective;
}

