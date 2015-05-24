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
void Category::edit(std::string oldCategory, std::string newCategory)
{
	pointer_values_equal<std::string> eq = { oldCategory };
	std::vector<std::string*>::iterator it = find_if(Category::categoryVector->begin(), Category::categoryVector->end(), eq);
	if (it != Category::categoryVector->end()) //if found oldCategory within categoryVector
	{
		**it = newCategory;
	}
	else
	{
		throw std::exception("oldCategory is not found within categoryVector");
	}
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
//std::vector<std::string*>::iterator Category::findIterator(std::string *category)
//{
//	return find_if(
//		categoryVector->begin(),
//		categoryVector->end(),
//		[&category](const std::string *p)
//	{
//		return *category == *p;
//	});
//}
std::vector<std::string*>* Category::getCategoryVector() { return categoryVector; }
//bool operator==(const Category &lhs, const Category &rhs)
//{
//	return lhs.categoryVector == rhs.categoryVector;
//}
//const std::vector<Category> Category::categoryVector = new std::vector<Category>();