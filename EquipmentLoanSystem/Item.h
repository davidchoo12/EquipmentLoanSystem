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
	void printItem() const;
	bool compareItem(Item &item) const;
	void addCategory(std::string *category);
	Category getCategories() const;
	//~Item();
private:
	std::string name;
	Category *itemCategories;
	bool onLoan;
};