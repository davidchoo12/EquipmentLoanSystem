#include <iostream>
#include <ctime>
#include "Item.h"

Item::Item(std::string name, std::vector<std::string*> &category)
{
	Item::name = name;
	Item::itemCategories = new Category(category);
	Item::onLoan = false;

	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t);
	Item::timeCreated = "to be fixed, coming soon";/*(now.tm_year + 1900) + '-' +
						(now.tm_mon + 1) + '-' +
						now.tm_mday;*/
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
void Item::setName(std::string name)
{
	Item::name = name;
}
void Item::setCategories(std::vector<std::string*> &categories)
{
	delete Item::itemCategories;
	Item::itemCategories = new Category(categories);
}
void Item::printItem() const
{
	std::cout << "----------" << Item::name << "----------" << std::endl;
	std::cout << "Categories: ";
	Item::itemCategories->displayAll();
	std::cout << "On Loan: " << Item::onLoan << std::endl;
	std::cout << "Time Created: " << Item::timeCreated << std::endl;
}
void Item::addCategory(std::string *category)
{
	itemCategories->add(category);
}
void Item::removeCategory(std::string &category)
{
	itemCategories->remove(category);
}
Category Item::getCategories() const
{
	return *itemCategories;
}
//Item::~Item()
//{
//	delete this;
//}