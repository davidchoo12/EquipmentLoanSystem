#pragma once

#include <string>
#include <vector>
//#include "Item.h";
class Category
{
public:
	Category(std::string categoryName);
	int size() const;
	void display(int start, int end) const;
	void add(std::string category);
	void edit(std::string oldCategory, std::string newCategory);
	void remove(std::string category);
	std::string getCategory();
	//static std::vector<std::string> *globalCategories;
	//const static std::vector<Category> *categoryVector;
	//static std::vector<Item> items;
	friend bool operator==(const Category &lhs, const Category &rhs);
private:
	std::string categoryName;
	//vector<Item*> test;
};