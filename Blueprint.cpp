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
