#include "Blueprint.h"

Blueprint::Blueprint(const string &name, const string &description, int timeMod, int dmgType, int increase) :
    Item(name, description, timeMod){
    this->dmgType = dmgType;
    this->increase = increase;
}

void Blueprint::enhanceTrap(Trap& t){
    if(dmgType != t.getDmgTypeNum()) return;
    t.setMaxDmg(increase);
}

string Blueprint::getDmgType(){
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

int Blueprint::getIncrease(){
    return increase;
}


