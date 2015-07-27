#include <iostream>
#include <ctime>
#include "Item.h"

Item::Item(std::string name, std::vector<std::string*> &category)
{
	Item::name = name;
	Item::itemCategories = new Category(category);

	time_t now = time(0);   // get time now
	/*struct tm now;
	localtime_s(&now, &t);*/
	//std::string	dt = ctime(&now); (apparently ctime is "unsafe")
	tm ltm;
	localtime_s(&ltm, &now);
	Item::timeCreated = std::to_string(ltm.tm_year + 1900) + "-" +
						std::to_string(ltm.tm_mon + 1) + "-" +
						std::to_string(ltm.tm_mday);
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
void Item::f(const char *s) const
{
	printf("%*s%*s\n", 20 + strlen(s) / 2, s, 20 - strlen(s) / 2, "");
}
void Item::printItem() const
{
	f((Item::name + " (Unloanable)").c_str());
	std::cout << "Categories: ";
	Item::itemCategories->displayAll();
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
bool Item::isA(std::string* category)
{
	return Item::itemCategories->has(category);
}