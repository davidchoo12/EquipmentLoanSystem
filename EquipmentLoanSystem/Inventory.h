#pragma once

#include <string>
#include <list>
#include "Item.h"

class Inventory
{
public:
	Inventory();
	int size() const; //might be used
	void displayAll() const;
	void add(Item *item);
	void displaySearch(std::string &searchKey);
	void displaySearchByCategory(std::string &searchKey);
	Category* getAllCategories() const; //might be used
	/*for choosing which pointer to the category string to use,
	if the category string pointer is alr in the global category then return the pointer in global category
	else add the category string pointer to the global category and return the original category string pointer
	*/
	std::string* decideWithAllCategories(std::string* category);
	std::vector<Item*> getItemsByName(std::string &searchKey);
	//std::vector<Item*> Inventory::getItemsByCategory(std::string &searchKey);
	std::vector<Item*> getAllItems();
	void deleteItem(Item *item);
	//friend void setItemCategory(Item *item, std::vector<std::string*> *category);
private:
	std::list<Item*> *itemCollection;
	Category *globalCategories;
	//class to store each category string and its matching items
	//struct CategoryItems
	//{
	//public:
	//	CategoryItems(std::string *category);
	//	std::string *category;
	//	std::vector<Item*> *items;
	//};
	////categoryItemsVector will be a helping object for recording the items with the same categories
	//std::vector<CategoryItems> *categoryItemsVector;
	//CategoryItems* searchCategory(std::string *category)
	//{
	//	std::vector<CategoryItems>::iterator ciit;
	//	for (ciit = categoryItemsVector->begin(); ciit != categoryItemsVector->end(); ciit++)
	//	{
	//		if (ciit->category == category) return &*ciit;
	//	}
	//}
	//std::vector<CategoryItems*> searchItemFromCategoryItems(Item *item)
	//{
	//	std::vector<CategoryItems*> *result = new std::vector<CategoryItems*>();
	//	std::vector<CategoryItems>::iterator ciit;
	//	std::vector<Item*>::iterator iit;
	//	for (ciit = categoryItemsVector->begin(); ciit != categoryItemsVector->end(); ciit++)
	//	{
	//		for (iit = ciit->items->begin(); iit != ciit->items->end(); iit++)
	//		{
	//			if (*iit == item)
	//			{
	//				result->push_back(&*ciit);
	//			}
	//		}
	//	}
	//	return *result;
	//}
};