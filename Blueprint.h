#ifndef BLUEPRINT_H
#define BLUEPRINT_H

#include "Trap.h"

class Blueprint {
private:
    int dmgType;
    int increase;
public:
    Blueprint(int dmgType, int increase);
    void enhanceTrap(Trap* t);
};

#endif // BLUEPRINT_H
