//*************************************************************
// Author: David Choo
// 
// class Item.h
// This class represents an item that can be stored into the inventory. One item can contain multiple category strings with the Category object. An item can either be loanable or not.
//*************************************************************
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "Category.h"

class Item
{
public:
	//Item constructor
	//Postcondition: name and itemCategories is initialised per the arguments, timeCreated is automatically generated
	Item(std::string name, std::vector<std::string*> &category);

	//Function to get the item's name
	//Postcondition: the name string is returned
	std::string getName() const;

	//Function to set the item's name
	//Postcondition: the name string is assigned with the argument's name
	void setName(std::string name);

	//Function to set the item's categories
	//Postcondition: the current itemCategories is deleted and reinitialised with the argument's categories
	void setCategories(std::vector<std::string*> &categories);

	//Virtual function to output the item
	//Postcondition: the item's details is printed
	virtual void printItem() const;

	//Function to get the item's categories
	//Postcondition: the current itemCategories is returned
	Category getCategories() const;
	//~Item();
protected:
	std::string name;
	Category *itemCategories;
	std::string timeCreated;

	//Function to print the argument with center alignment using printf
	//Postcondition: the argument is printed with width specified printf
	void f(const char *s) const;
};