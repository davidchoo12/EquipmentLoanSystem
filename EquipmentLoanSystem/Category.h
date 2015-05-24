#pragma once

#include <string>
#include <vector>
//#include "Item.h";
class Category
{
public:
	Category();
	Category(std::vector<std::string*> &categoryVector);
	int size() const;
	void displayAll() const;
	void displayBetween(int start, int end) const;
	void add(std::string *categoryItem);
	void edit(std::string oldCategoryItem, std::string newCategoryItem);
	void remove(std::string categoryItem);
	std::vector<std::string*>* getCategoryVector();
	//static std::vector<std::string> *globalCategories;
	//const static std::vector<Category> *categoryVector;
	//static std::vector<Item> items;
	//friend bool operator==(const Category &lhs, const Category &rhs);
private:
	std::vector<std::string*> *categoryVector;
	//vector<Item*> test;
};