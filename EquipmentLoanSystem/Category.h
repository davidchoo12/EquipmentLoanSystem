#pragma once

#include <string>
#include <vector>

class Category
{
public:
	Category();
	Category(std::vector<std::string*> &categoryVector);
	void displayAll() const;
	void add(std::string *categoryItem);
	void edit(std::string oldCategoryItem, std::string newCategoryItem); //to be used
	void remove(std::string &categoryItem);
	std::vector<std::string*>* getCategoryVector();
private:
	std::vector<std::string*> *categoryVector;
};