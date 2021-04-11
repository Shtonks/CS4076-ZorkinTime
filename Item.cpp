#include "Item.h"

Item::Item(){}

Item::Item(string n, string d, int t) {
	name = n;
	description = d;
    timeMod = t;
    amount = 1;
}

string Item::getName() const{
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

bool Item::operator== (const Item & rhs) const {
   return (name == rhs.getName());
}

string Item::toString(){
    return "Name: " + name +
           "\nAmount: " + to_string(amount) +
           "\nTime Taken: " + to_string(timeMod) +
           "\nDescription: " + description;
}
