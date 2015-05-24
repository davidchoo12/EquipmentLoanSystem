#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "Category.h"

class Item
{
public:
	Item(std::string name, std::vector<std::string*> &category);
	std::string getName() const;
	void setName(std::string name); //to be used
	void printItem() const;
	void addCategory(std::string *category); //to be used
	void removeCategory(std::string &category); //to be used
	Category getCategories() const;
	//~Item();
private:
	std::string name;
	Category *itemCategories;
	bool onLoan; //to be used
	//TODO fix timeCreated string
	std::string timeCreated;
};