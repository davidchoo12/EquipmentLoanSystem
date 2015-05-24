#include <iostream>
#include <string>
#include "Category.h"

Category::Category(std::string categoryName)
{
	Category::categoryName = categoryName;
	//std::vector<std::string> *globalCategories;
	//globalCategories = new std::vector<std::string>();
	//globalCategories->push_back(categoryName);
	//Category::categories = new std::vector<std::string>();
	//Category::categories->push_back(categoryName);
}
int Category::size() const { return 0; }
void Category::display(int start, int end) const {}
void Category::add(std::string category) { }
void Category::edit(std::string oldCategory, std::string newCategory) {}
void Category::remove(std::string category) {}
std::string Category::getCategory() { return categoryName; }
bool operator==(const Category &lhs, const Category &rhs)
{
	return lhs.categoryName == rhs.categoryName;
}
//const std::vector<Category> Category::categoryVector = new std::vector<Category>();