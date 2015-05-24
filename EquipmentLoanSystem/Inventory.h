#pragma once

#include <string>
#include <list>
#include "Item.h"

class Inventory
{
public:
	Inventory();
	int size() const;
	void displayAll() const;
	void displayBetween(int start, int end) const;
	void add(Item &item);
	void edit(Item item);
private:
	std::list<Item> *itemCollection;
};