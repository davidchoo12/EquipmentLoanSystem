#include <iostream>
#include <algorithm>
#include "Inventory.h"

Inventory::Inventory()
{
	itemCollection = new std::list<Item*>();
	//Inventory::categoryItemsVector = new std::vector<CategoryItems>();
	globalCategories = new Category();
}
void Inventory::add(Item *item)
{
	itemCollection->push_back(item);
}
std::vector<Item*> Inventory::getItemsByName(std::string &searchKey)
{
	std::list<Item*>::iterator it;
	std::vector<Item*> *resultItemVector;
	resultItemVector = new std::vector<Item*>();
	//int counter = 0;
	for (it = itemCollection->begin(); it != itemCollection->end(); ++it)
	{
		//if searchKey is a substring of the item's name
		if ((*it)->getName().find(searchKey) != std::string::npos)
		{
			/*counter++;
			std::cout << counter;
			it->printItem();*/
			resultItemVector->push_back(*it);
		}
	}
	return *resultItemVector;
}
std::vector<Item*> Inventory::getAllItems()
{
	std::vector<Item*> allItems = *(new std::vector<Item*>());
	std::list<Item*>::iterator icit;
	for (icit = Inventory::itemCollection->begin(); icit != Inventory::itemCollection->end(); icit++)
	{
		allItems.push_back(*icit);
	}
	return allItems;
}
Category* Inventory::getAllCategories() const
{
	return globalCategories;
}
void Inventory::deleteItem(Item *item)
{
	std::list<Item*>::iterator icit = std::find(itemCollection->begin(), itemCollection->end(), item);
	itemCollection->erase(icit);
}