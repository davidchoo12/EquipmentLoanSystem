//*************************************************************
// Author: David Choo
// 
// class InventoryManager.h
// This class handles the actions to be done on the inventory as well as keeping track of items of the same categories with the inner class CategoryItems.
//*************************************************************
#pragma once

#include <string>
#include "Inventory.h"
#include "LoanableItem.h"

class InventoryManager
{
public:
	//Constructor with parameters 
	//Postcondition: The constructor saves the inventory address to a pointer and creates a new CategoryItems vector object.
	InventoryManager(Inventory &inventory);

	//Function to return a vector of items with names that contain the searchKey string
	//Postcondition: return a sorted vector of items from the inventory's getItemsByName function
	std::vector<Item*> getItemsByName(std::string searchKey);

	//Function to return a vector of loanable items with names that contain the searchKey string
	//Postcondition: return a filtered vector of items with matching name
	std::vector<LoanableItem*> getLoanableItemsByName(std::string searchKey);

	//Function to return a vector of items with categories that contain the searchKey string
	//Postcondition: return a sorted vector of items leveraging on CategoryItems to find the items
	std::vector<Item*> getItemsByCategory(std::string searchKey);

	//Function to return a vector of loanable items with categories that contain the searchKey string
	//Postcondition: return a filtered vector of items with matching categories
	std::vector<LoanableItem*> getLoanableItemsByCategory(std::string searchKey);

	//Function to return a vector of all items in the inventory
	//Postcondition: return a sorted vector of all items
	std::vector<Item*> getAllItems();

	//Function to return a vector of all loanable items in the inventory
	//Postcondition: return a filtered vector of all loanable items
	std::vector<LoanableItem*> getAllLoanableItems();

	//Function to add an item to the inventory while keeping track of its categories with CategoryItems
	//Postcondition: item adds into inventory, categoryItemsVector is updated with the new item's categories
	void addItem(std::string &name, std::vector<std::string*> &category, bool isLoanable);

	//Function to edit an item's categories
	//Postcondition: the item's categories and the categoryItemsVector are updated
	void editItemCategory(Item *item, std::vector<std::string*> &name);

	//Function to delete one item
	//Postcondition: the item is removed from the inventory and the categoryItemsVector is updated
	void deleteItem(Item *item);

	//Function to return a pointer to a category string after comparing it with the strings in the CategoryItems of categoryItemsVector
	//Postcondition: if the category string exist in the inventory's globalCategories, return the globalCategories's category string pointer, else add the pointer to the globalCategories and return the original pointer
	std::string* decideWithAllCategories(std::string* category);

private:
	//the inventory being managed
	Inventory *inventory;

	//Function to sort item vector
	//Postcondition: the item vector is sorted by the items' names
	void sort(std::vector<Item*> &itemVector);

	//Function to return a filtered vector of LoanableItems from the vector of Items
	//Postcondition: a vector of LoanableItems is extracted from the vector of Items
	std::vector<LoanableItem*> getLoanableItemsFromItems(std::vector<Item*> itemVector);

	//Class to store each category string and its matching items
	class CategoryItems
	{
	public:
		CategoryItems(std::string *category);
		std::string *category;
		std::vector<Item*> *items;
		void removeItem(Item *item);
		/*~CategoryItems()
		{
			delete category;
			delete items;
		}*/
	};

	//categoryItemsVector will be a helping object for recording the items with the same categories
	std::vector<CategoryItems*> *categoryItemsVector;

	//Function to return the CategoryItems object with the matching category string pointer
	//Postcondition: the categoryItemsVector is traversed to check for each CategoryItems of their category string pointer
	CategoryItems* getCategoryItemsByCategory(std::string *category);

	//Function to return the vector of CategoryItems which contains the item
	//Postcondition: the categoryItemsVector is traversed to check for each CategoryItems of their items pointer vector whether that they contain the argument's item pointer
	std::vector<CategoryItems*> getCategoryItemsByItem(Item *item);

	//Function to remove a CategoryItems object
	//Postcondition: the CategoryItems object is first removed from categoryItemsVector before being deleted
	void removeCategoryItems(CategoryItems* ci);
};