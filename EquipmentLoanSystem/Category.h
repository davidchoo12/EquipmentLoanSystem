//*************************************************************
// Author: David Choo
// 
// class Category.h
// This class stores the vector of category strings for items and inventories.
//*************************************************************
#pragma once

#include <string>
#include <vector>

class Category
{
public:
	//Default constructor
	//Postcondition: the categoryVector is initialised
	Category();

	//Parameterised constructor
	//Postcondition: the categoryVector is assigned with the argument's categoryVector
	Category(std::vector<std::string*> &categoryVector);

	//Function to print the categories
	//Postcondition: the categoryVector is traversed to print every category strings as a one line list
	void displayAll() const;

	//Function to add a category string
	//Postcondition: the argument is pushed into categoryVector and it is resorted
	void add(std::string *categoryItem);

	//Function to remove a category string
	//Postcondition: the argument is searched through the categoryVector and it is removed if found, else an exception is thrown. The categoryVector is then resorted
	void remove(std::string &categoryItem);

	//Function to return a vector of the category strings pointers
	//Postcondition: the categoryVector is returned
	std::vector<std::string*>* getCategoryVector();

private:
	//A vector of string pointers that points to the category strings
	std::vector<std::string*> *categoryVector;
};