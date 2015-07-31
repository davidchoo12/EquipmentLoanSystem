//*************************************************************
// Author: David Choo
// 
// class Inventory.h
// This class acts as a database that stores a list of items and a list of categories of the items.
//*************************************************************
#pragma once

#include <string>
#include <list>
#include "Item.h"

class Inventory
{
public:
	//Default constructor
	//Postcondition: initialises itemCollection and globalCategories
	Inventory();

	//Function to add an item into the inventory
	//Postcondition: the item is added into the itemCollection list
	void add(Item *item);

	//Function to return the items with a name containing the argument's searchKey
	//Postcondition: the itemCollection is traversed to compare each item's name with searchKey
	std::vector<Item*> getItemsByName(std::string &searchKey);

	//Function to return all the items as a vector
	//Postcondition: the itemCollection is traversed to add every item into a vector which is then returned
	std::vector<Item*> getAllItems();

	//Function to return the globalCategories
	//Postcondition: the globalCategories pointer is returned
	Category* getAllCategories() const;

	//Function to delete an item from the inventory
	//Postcondition: the item is removed from the itemCollection list
	void deleteItem(Item *item);
private:
	std::list<Item*> *itemCollection;
	Category *globalCategories;
};