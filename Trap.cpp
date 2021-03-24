#include "Trap.h"
#include <string>

Trap::Trap(string name, string description, int timeMod, string dmgType,int baseDmg, int maxDmg, bool effective){
    Item(name,description,timeMod);
    this->dmgType = dmgType;
    this->baseDmg = baseDmg;
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
    dealtDmg = rand() % (maxDmg-baseDmg) + baseDmg;
} //calculates damage dealt between baseDmg - maxDmg

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

