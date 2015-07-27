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
	void setCategories(std::vector<std::string*> &categories);
	virtual void printItem() const;
	void addCategory(std::string *category); //to be used
	void removeCategory(std::string &category); //to be used
	bool isA(std::string* category);
	Category getCategories() const;
	//~Item();
protected:
	std::string name;
	Category *itemCategories;
	std::string timeCreated;
	void f(const char *s) const;
};