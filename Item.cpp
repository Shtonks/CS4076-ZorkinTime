#include "Item.h"

Item::Item(){}

Item::Item(string n, string d, int t) {
	name = n;
	description = d;
    timeMod = t;
    amount = 1;
}

string Item::getName(){
	return name;
}

void Item::setName(string name){
    this->name = name;
}

string Item::getDescription(){
	return description;
}

void Item::setDescription(string desc){
    description = desc;
}

int Item::getTimeMod(){
    return timeMod;
}

void Item::setTimeMod(int newMod){
	timeMod = newMod;
}

int Item::getAmount(){
    return amount;
}

void Item::setAmount(int change){
    amount += change;
    if(amount == 0) owned = false;
}

bool Item::isOwned(){
    return owned;
}

void Item::setOwned(bool owned){
    this->owned = owned;
}

string Item::toString(){
    return "Name: " + name +
           "\nAmount: " + to_string(amount) +
           "\nTime Taken: " + to_string(timeMod) +
           "\nDescription: " + description;
}
