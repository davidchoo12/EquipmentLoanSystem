#pragma once

#include <string>
#include "Inventory.h"

class InventoryManager
{
public:
	InventoryManager(Inventory &inventory);
	std::vector<Item*> getItemsByName(std::string searchKey);
	std::vector<Item*> getItemsByCategory(std::string searchKey);
	std::vector<Item*> getAllItems();
	void addItem(std::string &name, std::vector<std::string*> &category);
	void editItemName(Item *item, std::string name);
	void editItemCategory(Item *item, std::vector<std::string*> &name);
	void deleteItem(Item *item);
	void deleteItemsOfCategory(std::string *category);
	std::string* decideWithAllCategories(std::string* category);
private:
	Inventory *inventory;
	//class to store each category string and its matching items
	class CategoryItems
	{
	public:
		CategoryItems(std::string *category);
		std::string *category;
		std::vector<Item*> *items;
		void removeItem(Item *item)
		{
			std::vector<Item*>::iterator it = find(items->begin(), items->end(), item);
			if (it != items->end())
				items->erase(it);
			else
				std::cout << "Item not found in the CategoryItems" << std::endl;
		}
		/*~CategoryItems()
		{
			delete category;
			delete items;
		}*/
	};
	//categoryItemsVector will be a helping object for recording the items with the same categories
	std::vector<CategoryItems*> *categoryItemsVector;
	CategoryItems* getCategoryItemsByCategory(std::string *category)
	{
		std::vector<CategoryItems*>::iterator ciit;
		for (ciit = categoryItemsVector->begin(); ciit != categoryItemsVector->end(); ciit++)
		{
			if ((*ciit)->category == category) return *ciit;
		}
		return nullptr;
	}
	std::vector<CategoryItems*> getCategoryItemsByItem(Item *item)
	{
		std::vector<CategoryItems*> *result = new std::vector<CategoryItems*>();
		std::vector<CategoryItems*>::iterator ciit;
		std::vector<std::string*>::iterator cit;
		std::vector<Item*>::iterator iit;
		for (ciit = categoryItemsVector->begin(); ciit != categoryItemsVector->end(); ciit++)
		{
			for (cit = item->getCategories().getCategoryVector()->begin(); cit != item->getCategories().getCategoryVector()->end(); cit++)
			{
				if ((*ciit)->category == *cit)
				{
					for (iit = (*ciit)->items->begin(); iit != (*ciit)->items->end(); iit++)
					{
						if (*iit == item)
						{
							result->push_back(*ciit);
						}
					}
				}
			}
		}
		return *result;
	}
	void removeCategoryItems(CategoryItems* ci)
	{
		std::vector<CategoryItems*>::iterator ciit;
		for (ciit = categoryItemsVector->begin(); ciit != categoryItemsVector->end(); ciit++)
		{
			if (*ciit == ci)
			{
				categoryItemsVector->erase(ciit);
				delete ci;
				return;
			}
		}
	}
};