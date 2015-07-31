#include <iostream>
#include <ctime>
#include "Item.h"
#include <Windows.h>

Item::Item(std::string name, std::vector<std::string*> &category)
{
	Item::name = name;
	Item::itemCategories = new Category(category);

	time_t now = time(0); // get current time
	tm ltm;
	localtime_s(&ltm, &now);
	Item::timeCreated = std::to_string(ltm.tm_year + 1900) + "-" +
						std::to_string(ltm.tm_mon + 1) + "-" +
						std::to_string(ltm.tm_mday);
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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 252);
	f((Item::name + " (Unloanable)").c_str());
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "Categories: ";
	Item::itemCategories->displayAll();
	std::cout << "Time Created: " << Item::timeCreated << std::endl;
}
Category Item::getCategories() const
{
	return *itemCategories;
}
//Item::~Item()
//{
//	delete this;
//}