#include <iostream>
#include "Item.h"

Item::Item(std::string name, std::vector<std::string*> &category)
{
	Item::name = name;
	Item::onLoan = false;
	Item::itemCategories = new Category(category);
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
	Item::itemCategories->displayAll();
}
//TODO find out the purpose of this method
bool Item::compareItem(Item &item) const
{
	return Item::name == item.name;
}
void Item::addCategory(std::string *category)
{
	itemCategories->add(category);
}
Category Item::getCategories() const
{
	return *itemCategories;
}
//Item::~Item()
//{
//	delete this;
//}