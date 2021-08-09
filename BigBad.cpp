#include "Bigbad.h"

BigBad::BigBad(int health) {
    maxHealth = health;
    currHealth = health;
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

int BigBad::getMaxHealth(){
    return maxHealth;
}

int BigBad::getCurrHealth(){
    return currHealth;
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

void BigBad::takeDmg(int dmg){
    currHealth -= dmg;
}

string BigBad::leaveDungeon(Room* rooms[], int numRooms){
    for(int i = 0; i < numRooms; i++){
        if(rooms[i]->getTrapInRoom() == nullptr) continue;
        currHealth -= rooms[i]->getTrapInRoom()->getDealtDmg();
        if(currHealth <= 0) break;
    }
    string out;
    out = (currHealth > 0)? "Success" : "Failure";
    return out;
}
