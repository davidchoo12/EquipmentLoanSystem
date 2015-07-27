#include <iostream>
#include <string>
#include "InventoryManager.h"
using namespace std;

bool itemTitleAscending(Item *lhs, Item *rhs) { return lhs->getName().compare(rhs->getName()) < 0; }
InventoryManager::InventoryManager(Inventory &inventory)
{
	InventoryManager::inventory = &inventory;
	InventoryManager::categoryItemsVector = new std::vector<CategoryItems*>();
}
void InventoryManager::sort(std::vector<Item*> &itemVector)
{
	std::sort(itemVector.begin(), itemVector.end(), itemTitleAscending);
}
std::vector<LoanableItem*> InventoryManager::getLoanableItemsFromItems(std::vector<Item*> itemVector)
{
	std::vector<LoanableItem*> result;
	std::vector<Item*>::iterator ivit;
	for (ivit = itemVector.begin(); ivit != itemVector.end(); ivit++)
	{
		LoanableItem *li = dynamic_cast<LoanableItem*>(*ivit);
		//if (typeid(*ivit).name() == "class LoanableItem")
		if (li) //if the conversion succeed, li would not be null so add it to the result vector
			result.push_back(li);
	}
	return result;
}
std::vector<Item*> InventoryManager::getItemsByName(std::string searchKey)
{
	std::vector<Item*> result = InventoryManager::inventory->getItemsByName(searchKey);
	sort(result);
	return result;
}
std::vector<Item*> InventoryManager::getItemsByCategory(std::string searchKey)
{
	std::vector<CategoryItems*>::iterator it;
	std::vector<Item*>::iterator it2;
	std::vector<Item*> resultItemVector;
	resultItemVector = *(new std::vector<Item*>());
	//int counter = 0;
	for (it = categoryItemsVector->begin(); it != categoryItemsVector->end(); ++it)
	{
		if ((*it)->category->find(searchKey) != std::string::npos)
		{
			for (it2 = (*it)->items->begin(); it2 != (*it)->items->end(); it2++)
			{
				//counter++;
				//std::cout << counter;
				//(*it2)->printItem();
				// if not in resultItemVector then add in, to prevent duplicates
				Item* currItem = *it2;
				std::vector<Item*>::iterator rivit = std::find_if(
					resultItemVector.begin(),
					resultItemVector.end(),
					[&currItem](const Item *p)
				{
					return currItem->getName() == p->getName();
				});
				if (rivit == resultItemVector.end())
					resultItemVector.push_back(currItem);
			}
		}
	}
	sort(resultItemVector);
	return resultItemVector;
}
std::vector<LoanableItem*> InventoryManager::getLoanableItemsByName(std::string searchKey)
{
	return InventoryManager::getLoanableItemsFromItems(InventoryManager::getItemsByName(searchKey));
}
std::vector<LoanableItem*> InventoryManager::getLoanableItemsByCategory(std::string searchKey)
{
	return InventoryManager::getLoanableItemsFromItems(InventoryManager::getItemsByCategory(searchKey));
}
std::vector<LoanableItem*> InventoryManager::getAllLoanableItems()
{
	return InventoryManager::getLoanableItemsFromItems(InventoryManager::getAllItems());
}
std::vector<Item*> InventoryManager::getAllItems()
{
	std::vector<Item*> result = InventoryManager::inventory->getAllItems();
	sort(result);
	return result;
}
void InventoryManager::addItem(std::string &name, std::vector<std::string*> &category, bool isLoanable)
{
	std::vector<std::string*>::iterator cfiit;
	for (cfiit = category.begin(); cfiit != category.end(); cfiit++) { *cfiit = InventoryManager::decideWithAllCategories(*cfiit); }
	Item *toBeAdded;
	if (isLoanable)
	{
		toBeAdded = new LoanableItem(name, category);
		InventoryManager::inventory->add(toBeAdded);
	}
	else
	{
		toBeAdded = new Item(name, category);
		InventoryManager::inventory->add(toBeAdded);
	}
	//updates the categoryItemsVector
	std::vector<std::string*>::iterator it;
	std::vector<CategoryItems*>::iterator it2;
	for (it = toBeAdded->getCategories().getCategoryVector()->begin(); it != toBeAdded->getCategories().getCategoryVector()->end(); ++it)
	{
		for (it2 = categoryItemsVector->begin(); it2 != categoryItemsVector->end(); ++it2)
		{
			//if category of the item matches a category in a categoryItems, add the item to the corresponding items vector
			if ((*it) == (*it2)->category)
				(*it2)->items->push_back(toBeAdded);
		}
	}
}
void InventoryManager::editItemName(Item *item, std::string name)
{
	item->setName(name);
}
void InventoryManager::editItemCategory(Item *item, std::vector<std::string*> &categories)
{
	//1. if any of the string from categories is found in the item, remove the string from categories
	//2. remove any other category strings from item Category
	//3. add all strings left in categories into item Category
	//4. remove item from CategoryItems of the category strings
	//5. if CategoryItems of the category strings removed does not have anymore item, remove the CategoryItems
	//6. if any of the string from categories is found in any CategoryItems, add item into that CategoryItems
	//7. else add new CategoryItems of the string and add the item into the CategoryItems
	//PSUDO CODE:
	//for all the strings from item Category
	//	if it is NOT in categories
	//		remove it from item Category(2)
	//		remove item from CategoryItems of it(4)
	//		if (CategoryItems of it)'s items is empty (5)
	//			remove CategoryItems of it from categoryItemsVector
	//			remove CategoryItems
	//		else
	//		remove it from categories(1)
	//		for all strings from categories
	//			add into item Category(3) //if unable to: add categories into item Category (find way to efficiently append vector) (3)
	//			if it is a category from CategoryItems in categoryItemsVector(6)
	//				add item into the CategoryItems
	//			else (7)
	//			add new CategoryItems of it
	//			add item into the new CategoryItems of it

	std::vector<std::string*>::iterator spit; // String Pointer ITerator = SPIT lol
	for (spit = item->getCategories().getCategoryVector()->begin(); spit != item->getCategories().getCategoryVector()->end();)
	{
		std::vector<std::string*>::iterator cit = find(categories.begin(), categories.end(), *spit);
		if (cit == categories.end()) // if the current itemCategory is not one of the categories
		{
			//remove the item from the CategoryItems of the current itemCategory
			CategoryItems *categoryItemsOfCurrentCategory = getCategoryItemsByCategory(*spit);
			categoryItemsOfCurrentCategory->removeItem(item);
			//if the CategoryItems of the current itemCategory is empty, remove the category from the globalCategories, remove the CategoryItems from the categoryItemsVector and delete the CategoryItems
			if (categoryItemsOfCurrentCategory->items->size() == 0)
			{
				inventory->getAllCategories()->remove(**spit);
				removeCategoryItems(categoryItemsOfCurrentCategory);
			}
			//remove the current itemCategory
			spit = item->getCategories().getCategoryVector()->erase(spit); //returns iterator pointing to the place where the erased object was (basically where the next object is currently at), so no need spit++
		}
		else
		{
			categories.erase(cit);
			spit++;
		}
	}
	//the categories now contains strings not in itemCategories
	//append the categories into the item category vector
	item->getCategories().getCategoryVector()->insert(item->getCategories().getCategoryVector()->end(), categories.begin(), categories.end());
	
	for (spit = categories.begin(); spit != categories.end(); spit++)
	{
		//if the current category is already a CategoryItems in categoryItemsVector, just add the item into the CategoryItems
		CategoryItems *currentCategoryItems = getCategoryItemsByCategory(*spit);
		if (currentCategoryItems)
		{
			currentCategoryItems->items->push_back(item);
		}
		//else add the category into the globalCategories, create new CategoryItems of the current category, add in the item, add it into the categoryItemsVector
		else
		{
			inventory->getAllCategories()->add(*spit);
			currentCategoryItems = new CategoryItems(*spit);
			currentCategoryItems->items->push_back(item);
			categoryItemsVector->push_back(currentCategoryItems);
		}
	}
}
void InventoryManager::deleteItem(Item *item)
{
	std::vector<std::string*>::iterator spit; // String Pointer ITerator = SPIT lol
	for (spit = item->getCategories().getCategoryVector()->begin(); spit != item->getCategories().getCategoryVector()->end();)
	{
		//remove the item from the CategoryItems of the current itemCategory
		CategoryItems *categoryItemsOfCurrentCategory = getCategoryItemsByCategory(*spit);
		categoryItemsOfCurrentCategory->removeItem(item);
		//if the CategoryItems of the current itemCategory is empty, remove the category from the globalCategories, remove the CategoryItems from the categoryItemsVector and delete the CategoryItems
		if (categoryItemsOfCurrentCategory->items->size() == 0)
		{
			inventory->getAllCategories()->remove(**spit);
			removeCategoryItems(categoryItemsOfCurrentCategory);
		}
		//remove the current itemCategory
		spit = item->getCategories().getCategoryVector()->erase(spit); //returns iterator pointing to the place where the erased object was (basically where the next object is currently at), so no need spit++
	}
	inventory->deleteItem(item);
	delete item;
}
//void InventoryManager::deleteItemsOfCategory(std::string *category)
//{
//	CategoryItems *ci = getCategoryItemsByCategory(category);
//	std::vector<Item*>::iterator iit;
//	for (iit = ci->items->begin(); iit != ci->items->end(); iit++)
//	{
//		deleteItem(*iit);
//	}
//	delete ci;
//}
std::string* InventoryManager::decideWithAllCategories(std::string* category)
{
	Category *globalCategories = InventoryManager::inventory->getAllCategories();
	std::vector<std::string*>::iterator gcit =
		find_if(
		globalCategories->getCategoryVector()->begin(),
		globalCategories->getCategoryVector()->end(),
		[&category](const std::string *p) //lambda expression
	{
		return *category == *p;
	});
	//if not found in global categories
	if (gcit == globalCategories->getCategoryVector()->end())
	{
		globalCategories->add(category);
		categoryItemsVector->push_back(new CategoryItems(category));
		return category;
	}
	else //if found in global categories
	{
		return *gcit;
	}
}
InventoryManager::CategoryItems::CategoryItems(std::string *category)
{
	InventoryManager::CategoryItems::category = category;
	InventoryManager::CategoryItems::items = new std::vector<Item*>();
}