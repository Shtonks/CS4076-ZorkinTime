#include "Trap.h"
#include <string>

Trap::Trap(string name, string description, int timeMod, string dmgType,int baseDmg, int maxDmg){
    Item(name, description, timeMod);
    this->dmgType = dmgType;
    this->baseDmg = baseDmg;
    this->maxDmg = maxDmg;
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
           "\n"+ to_string(baseDmg)+ "-" + to_string(maxDmg) + " " + dmgType + "damage" +
           "\nDescription: " + getDescription();
}
