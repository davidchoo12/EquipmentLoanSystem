#include <iostream>
#include <list>
#include <string>
#include "Item.h"
#include "Inventory.h"

Inventory::Inventory()
{
	itemCollection = new std::list<Item>();
	/*std::vector<Item>::iterator it;
	for (int i = 0; i < 5; i++)
	{*/
	/*itemCollection->push_back(*(new Item("a", "cat1")));
	itemCollection->push_back(*(new Item("b", "cat1")));
	itemCollection->push_back(*(new Item("c", "cat1")));*/
	//}
}
int Inventory::size() const
{
	return itemCollection->size();
}
void Inventory::displayAll() const
{
	std::list<Item>::iterator it;
	for (it = itemCollection->begin(); it != itemCollection->end(); ++it)
	{
		it->printItem();
		std::cout << std::endl;
	}
}
void Inventory::displayBetween(int start, int end) const
{
	if (start >= 0 && start <= itemCollection->size() && end >= 0 && end <= itemCollection->size())
	{
		std::list<Item>::iterator it1 = itemCollection->begin();
		advance(it1, start);
		for (int i = start; i < end; i++)
		{
			it1->printItem();
			std::cout << std::endl;
			it1++;
		}
	}
	else
	{
		throw std::exception("out of range");
	}
}
void Inventory::add(Item &item)
{
	itemCollection->push_back(item);
}