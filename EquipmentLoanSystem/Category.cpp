#include <iostream>
#include <algorithm>
#include "Category.h"

bool alphabeticalAscending(std::string *lhs, std::string *rhs) { return lhs->compare(*rhs) < 0; }

// for comparing objects pointed by pointers in a pointer vector
template <typename T>
struct pointer_values_equal
{
	const T to_find;
	bool operator()(const T* other) const
	{
		return to_find == *other;
	}
};
Category::Category()
{
	Category::categoryVector = new std::vector<std::string*>();
}
Category::Category(std::vector<std::string*> &categoryVector)
{
	Category::categoryVector = &categoryVector;
	std::sort(Category::categoryVector->begin(), Category::categoryVector->end(), alphabeticalAscending);
}
void Category::displayAll() const
{
	std::vector<std::string*>::iterator it;
	for (it = categoryVector->begin(); it != categoryVector->end(); ++it)
	{
		std::cout << **it;
		std::string delimiter = (it != categoryVector->end() - 1 )? ", " : "";
		std::cout << delimiter;
	}
	std::cout << std::endl;
}
void Category::add(std::string *category)
{
	Category::categoryVector->push_back(category);
	std::sort(categoryVector->begin(), categoryVector->end(), alphabeticalAscending);
}
void Category::remove(std::string &category)
{
	pointer_values_equal<std::string> eq = { category };
	std::vector<std::string*>::iterator it = find_if(Category::categoryVector->begin(), Category::categoryVector->end(), eq);
	if (it != Category::categoryVector->end()) //if found category within categoryVector
	{
		categoryVector->erase(it);
	}
	else
	{
		throw std::exception("category is not found within categoryVector");
	}
	std::sort(categoryVector->begin(), categoryVector->end(), alphabeticalAscending);
}
std::vector<std::string*>* Category::getCategoryVector() { return categoryVector; }