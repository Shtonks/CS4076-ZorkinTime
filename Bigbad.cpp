#include "Bigbad.h"

BigBad::BigBad(int health) {
    this->health = health;
    genRisks();
}

string BigBad::typeToString(int dmgType){
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

void BigBad::genRisks(){
    srand(time(0));
    resistance = rand() % 6;
    vulnerability = rand() % 6;
    while(resistance == vulnerability) vulnerability = rand() % 6;
}

int BigBad::getHealth(){
    return health;
}

int BigBad::getResistance(){
    return resistance;
}

string BigBad::getResistanceString(){
    return typeToString(resistance);
}

int BigBad::getVulnerability(){
    return vulnerability;
}

string BigBad::getVulnerabilityString(){
    return typeToString(vulnerability);
}

void BigBad::leaveDungeon(Room* rooms[], int numRooms){
    for(int i = 0; i < numRooms; i++){
        if(rooms[i]->getTrapInRoom() == nullptr) continue;
        health -= rooms[i]->getTrapInRoom()->getDealtDmg();
        if(health <= 0) break;
    }
}
