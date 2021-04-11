#include "Blueprint.h"

Blueprint::Blueprint(int dmgType, int increase){
    this->dmgType = dmgType;
    this->increase = increase;
}

void Blueprint::enhanceTrap(Trap *t){
    if(dmgType != t->getDmgType()) return;
    t->setMaxDmg(increase);
}
