#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "Category.h"

class Item
{
public:
	Item(std::string name, std::vector<Category*> *category);
	std::string getName() const;
	void printItem() const;
	bool compareItem(Item &item) const;
	void addCategory(Category *category);
	std::vector<Category*> getCategories() const;
	//~Item();
private:
	std::string name;
	std::vector<Category*> *itemCategories;
	bool onLoan;
};