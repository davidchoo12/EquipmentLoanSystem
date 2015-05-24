#include <iostream>
#include <algorithm>
#include "Inventory.h"

Inventory::Inventory()
{
	itemCollection = new std::list<Item>();
	Inventory::categoryItemsVector = new std::vector<CategoryItems>();
	globalCategories = new Category();
}
int Inventory::size() const
{
	return itemCollection->size();
}
void Inventory::displayAll() const
{
	if (categoryItemsVector->size() == 0)
		std::cout << "No items found. You can add an item by entering 2." << std::endl;
	else
	{
		std::cout << "Total Items: " << itemCollection->size() << std::endl;
		std::list<Item>::iterator it;
		for (it = itemCollection->begin(); it != itemCollection->end(); ++it)
		{
			it->printItem();
			std::cout << std::endl;
		}
	}
}
void Inventory::add(Item &item)
{
	itemCollection->push_back(item);
	//updates the categoryItemsVector
	std::vector<std::string*>::iterator it;
	std::vector<CategoryItems>::iterator it2;
	for (it = item.getCategories().getCategoryVector()->begin(); it != item.getCategories().getCategoryVector()->end(); ++it)
	{
		for (it2 = categoryItemsVector->begin(); it2 != categoryItemsVector->end(); ++it2)
		{
			//if category of the item matches a category in a categoryItems, add the item to the corresponding items vector
			if((*it) == it2->category)
				it2->items->push_back(&item);
		}
	}
}
void Inventory::displaySearch(std::string &searchKey)
{
	std::list<Item>::iterator it;
	for (it = itemCollection->begin(); it != itemCollection->end(); ++it)
	{
		//if searchKey is a substring of the item's name
		if (it->getName().find(searchKey) != std::string::npos)
			it->printItem();
	}
}
//notice that i use the categoryItemsVector instead of searching one by one from the itemCollection list
void Inventory::displaySearchByCategory(std::string &searchKey)
{
	std::vector<CategoryItems>::iterator it;
	std::vector<Item*>::iterator it2;
	for (it = categoryItemsVector->begin(); it != categoryItemsVector->end(); ++it)
	{
		if (it->category->find(searchKey) != std::string::npos)
		{
			for (it2 = it->items->begin(); it2 != it->items->end(); ++it2)
			{
				(*it2)->printItem();
			}
		}
	}
}
Category* Inventory::getAllCategories() const
{
	return globalCategories;
}
std::string* Inventory::decideWithAllCategories(std::string* category)
{
	std::vector<std::string*>::iterator gcit =
		find_if(
		globalCategories->getCategoryVector()->begin(),
		globalCategories->getCategoryVector()->end(),
		[&category](const std::string *p) //lambda expression
	{
		return *category == *p;
	});
	//if not found in global categories
	if (gcit == globalCategories->getCategoryVector()->end())
	{
		globalCategories->add(category);
		categoryItemsVector->push_back(*(new CategoryItems(category)));
		return category;
	}
	else //if found in global categories
	{
		return *gcit;
	}
}
Inventory::CategoryItems::CategoryItems(std::string *category)
{
	Inventory::CategoryItems::category = category;
	Inventory::CategoryItems::items = new std::vector<Item*>();
}