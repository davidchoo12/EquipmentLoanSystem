#include <iostream>
#include "Item.h"

bool alphabeticalAscending(Category *lhs, Category *rhs) { return lhs->getCategory().compare(rhs->getCategory()) < 0; }

Item::Item(std::string name, std::vector<Category*> *category)
{
	Item::name = name;
	Item::onLoan = false;
	Item::itemCategories = new std::vector<Category*>();
	std::sort(category->begin(), category->end(), alphabeticalAscending);
	itemCategories = category;
	//std::vector<int> myvector(myints, myints + 4);
	//std::vector<int>::iterator it;

	//it = find(myvector.begin(), myvector.end(), 40);
	//if (it != myvector.end())
	//	std::cout << "Element found in myvector: " << *it << '\n';
	//else
	//	std::cout << "Element not found in myvector\n";
	//Item::categoryVector->push_back(*(new Category(category)));
}
std::string Item::getName() const
{
	return Item::name;
}
void Item::printItem() const
{
	std::cout << Item::name << std::endl;
	std::cout << "Categories: ";
	for (std::vector<Category*>::iterator i = itemCategories->begin(); i != itemCategories->end(); ++i)
	{
		std::cout << (*i)->getCategory() << ", ";
	}
}
bool Item::compareItem(Item &item) const
{
	return Item::name == item.name;
}
void Item::addCategory(Category *category)
{
	itemCategories->push_back(category);
	std::sort(itemCategories->begin(), itemCategories->end(), alphabeticalAscending);
}
std::vector<Category*> Item::getCategories() const
{
	return *itemCategories;
}
//Item::~Item()
//{
//	delete this;
//}