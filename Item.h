#pragma once

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
	private:
		string description;
		string name;
		int timeMod;

	public:
        Item();
        Item (string name, string description, int timeMod);
		string getName();
        void setName(string name);
		string getDescription();
        void setDescription(string desc);
        int getTimeMod();
		void setTimeMod(int newMod);
};
