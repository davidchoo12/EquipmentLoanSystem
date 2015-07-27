//There was some issue with the stack size limit that the app throws an exception whenever the app is closed
//I configured the stack size to be 10MB instead of the default 1MB and it resolves the issue

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "InventoryManager.h"
#include "Inventory.h"
#include "Category.h"
#include "Item.h"
#include <stdlib.h>
//#include <conio.h>

Inventory *globalInventory;
InventoryManager *globalInventoryManager;

void searchItem()
{/*
	char repeat = 'y';
	do
	{*/
		char choice;
		std::cout << "Do you want to search by Item name or Category or display all items? (enter 0 to go back)" << std::endl;
		std::cout << "1. Item name" << std::endl;
		std::cout << "2. Category" << std::endl;
		std::cout << "3. Display all Items" << std::endl;
		std::cin >> choice;
		std::vector<Item*> resultItemVector;
		std::string searchKey;
		switch (choice)
		{
		case '0': return;
			break;
		case '1':
			std::cout << "Enter the Item name: ";
			std::cin >> searchKey;
			resultItemVector = globalInventoryManager->getItemsByName(searchKey);
			break;
		case '2':
			std::cout << "Enter the Category: ";
			std::cin >> searchKey;
			resultItemVector = globalInventoryManager->getItemsByCategory(searchKey);
			break;
		case '3': resultItemVector = globalInventoryManager->getAllItems();
			break;
		default:
			std::cout << "Invalid Char" << std::endl;
			return;
		}
		// to print out resultItemVector items
		if (resultItemVector.size() == 0)
			std::cout << "No item found." << std::endl;
		else
		{
			std::cout << "Total Items: " << resultItemVector.size() << std::endl;
			std::vector<Item*>::iterator rivit;
			for (rivit = resultItemVector.begin(); rivit != resultItemVector.end(); ++rivit)
			{
				(*rivit)->printItem();
				std::cout << std::endl;
			}
		}/*
		
		repeatConfirmation:
		std::cout << "Search another item again? y/n" << std::endl;
		std::cin >> repeat;
		repeat = tolower(repeat);
	} while (repeat == 'y');*/
}
std::vector<std::string*>* categoriesStringToVector(std::string commaDelimitedCategories)
{
	commaDelimitedCategories += ","; // so that the last categoryInput can be obtained (just a simple workaround)
	size_t pos = 0;
	std::string *token;
	std::vector<std::string*> *categoriesFromInput = new std::vector<std::string*>();
	while ((pos = commaDelimitedCategories.find(",")) != std::string::npos)
	{
		token = new std::string(commaDelimitedCategories.substr(0, pos));
		std::vector<std::string*>::iterator cfiit =
			std::find_if(
			categoriesFromInput->begin(),
			categoriesFromInput->end(),
			[&token](const std::string *p) //lambda expression
		{
			return *token == *p;
		});
		// if not in categoriesfrominput (not repetitive)
		if (cfiit == categoriesFromInput->end())
		{
			categoriesFromInput->push_back(token);
		}
		cfiit = categoriesFromInput->begin();
		//as each category is added, it is erased from the input string
		commaDelimitedCategories.erase(0, pos + 1);
	}
	return categoriesFromInput;
}

void addItem()
{/*
	char repeat = 'y';
	do
	{*/
		std::string nameInput;
		std::string categoryInput;
		std::cout << "Please enter item details" << std::endl;
		std::cout << "Name (without spaces, not working with spaces yet) (enter 0 to go back): ";
		std::cin >> nameInput;
		if (nameInput == "0") return;
		std::cout << "Category: (use commas to delimit multiple values, no spaces in after commas)" << std::endl;
		std::cin >> categoryInput;
		char confirm;
		std::cout << "Are you sure? y/n" << std::endl;
		std::cin >> confirm;
		confirm = tolower(confirm);
		if (confirm == 'y')
		{
			std::vector<std::string*> *categoriesFromInput = categoriesStringToVector(categoryInput);
			globalInventoryManager->addItem(nameInput, *categoriesFromInput, false);
			std::cout << "Item " << nameInput << " is added" << std::endl;
		}
		else if (confirm == 'n')
			std::cout << "You canceled adding " << nameInput << std::endl;
		else
			std::cout << "Invalid char" << std::endl;/*
		repeatConfirmation:
		std::cout << "Add another item again? y/n" << std::endl;
		std::cin >> repeat;
		repeat = tolower(repeat);
	} while (repeat == 'y');*/
}
void addItem(std::string itemName, std::string categories, bool isLoanable)
{
	std::vector<std::string*> *categoriesFromInput = categoriesStringToVector(categories);
	globalInventoryManager->addItem(itemName, *categoriesFromInput, isLoanable);
}
//template <class T>
//struct TypeIsItem
//{
//	static const bool value = false;
//};
//template <>
//struct TypeIsItem<Item>
//{
//	static const bool value = true;
//};
//template<class T>
//typename std::enable_if < std::is_same<Item, T>::value || std::is_same<LoanableItem, T>::value, T* >::type
Item* itemSelector(std::string prompt)
{
	char choice;
	std::cout << "Select the item you would like to " << prompt << ". Do you want to search by Item name or Category or display all items? (enter 0 to go back)" << std::endl;
	std::cout << "1. Item name" << std::endl;
	std::cout << "2. Category" << std::endl;
	std::cout << "3. Display all Items" << std::endl;
	std::cin >> choice;
	std::vector<Item*> resultItemVector;
	std::string searchKey;
	std::vector<Item*>::iterator rivit;
	switch (choice)
	{
	case '0': return nullptr;
		break;
	case '1':
		std::cout << "Enter the Item name: ";
		std::cin >> searchKey;
		resultItemVector = globalInventoryManager->getItemsByName(searchKey);
		break;
	case '2':
		std::cout << "Enter the Category: ";
		std::cin >> searchKey;
		resultItemVector = globalInventoryManager->getItemsByCategory(searchKey);
		break;
	case '3':
		resultItemVector = globalInventoryManager->getAllItems();
		break;
	default:
		std::cout << "Invalid Character" << std::endl;
		return nullptr;
	}
	if (resultItemVector.size() == 0)
	{
		std::cout << "No items found" << std::endl;
		return nullptr;
	}
	else
	{
		int counter = 0;
		for (rivit = resultItemVector.begin(); rivit != resultItemVector.end(); ++rivit)
		{
			std::cout << "Item " << ++counter << std::endl;
			(*rivit)->printItem();
			std::cout << std::endl;
		}
		std::cout << "Enter the number of the item you want to " << prompt << " or enter 0 to search again" << std::endl;
		std::cin >> choice;
		if (choice == '0') return nullptr;
		else //unnecessary since if choice is 0, the following code wont run
		{
			int choiceInt = choice - '1';
			resultItemVector.at(choiceInt)->printItem();
			return resultItemVector.at(choiceInt);
		}
	}
}
LoanableItem* loanableItemSelector(std::string prompt)
{
	char choice;
	std::cout << "Select the item you would like to " << prompt << ". Do you want to search by Item name or Category or display all items? (enter 0 to go back)" << std::endl;
	std::cout << "1. Item name" << std::endl;
	std::cout << "2. Category" << std::endl;
	std::cout << "3. Display all Items" << std::endl;
	std::cin >> choice;
	std::vector<LoanableItem*> resultItemVector;
	std::string searchKey;
	std::vector<LoanableItem*>::iterator rivit;
	switch (choice)
	{
	case '0': return nullptr;
		break;
	case '1':
		std::cout << "Enter the Item name: ";
		std::cin >> searchKey;
		resultItemVector = globalInventoryManager->getLoanableItemsByName(searchKey);
		break;
	case '2':
		std::cout << "Enter the Category: ";
		std::cin >> searchKey;
		resultItemVector = globalInventoryManager->getLoanableItemsByCategory(searchKey);
		break;
	case '3':
		resultItemVector = globalInventoryManager->getAllLoanableItems();
		break;
	default:
		std::cout << "Invalid Character" << std::endl;
		return nullptr;
	}
	if (resultItemVector.size() == 0)
	{
		std::cout << "No items found" << std::endl;
		return nullptr;
	}
	else
	{
		int counter = 0;
		for (rivit = resultItemVector.begin(); rivit != resultItemVector.end(); ++rivit)
		{
			std::cout << "Item " << ++counter << std::endl;
			(*rivit)->printItem();
			std::cout << std::endl;
		}
		std::cout << "Enter the number of the item you want to " << prompt << " or enter 0 to search again" << std::endl;
		std::cin >> choice;
		if (choice == '0') return nullptr;
		else //unnecessary since if choice is 0, the following code wont run
		{
			int choiceInt = choice - '1';
			resultItemVector.at(choiceInt)->printItem();
			return resultItemVector.at(choiceInt);
		}
	}
}
void editItem()
{
	Item* resultItem = itemSelector("edit");
	if (!resultItem) return; //if null, return
	std::cout << "New name (enter 0 if you dont want to change) : ";
	std::string input;
	std::cin >> input;
	if (input != "0")
		resultItem->setName(input);
		//globalInventoryManager->editItemName(resultItemVector.at(choiceInt), input);
	std::cout << "New categories (comma delimited, no spaces) (enter 0 if you dont want to change): " << std::endl;
	std::cin >> input;
	if (input != "0")
	{
		std::vector<std::string*> *categories = categoriesStringToVector(input);
		globalInventoryManager->editItemCategory(resultItem, *categories);
		/*std::vector<std::string*>::iterator cit;
		for (cit = categories->begin(); cit != categories->end(); ++cit) { *cit = globalInventoryManager->decideWithAllCategories(*cit); }
		resultItemVector.at(choiceInt)->setCategories(*categories);*/
	}
	resultItem->printItem();
}
void deleteOneItem()
{
	Item* resultItem = itemSelector("delete");
	if (!resultItem) return; //if null, return
	std::cout << "Are you sure you want to delete the item above? y/n" << std::endl;
	std::string input;
	std::cin >> input;
	if (input == "y")
	{
		std::string delItemName = resultItem->getName();
		globalInventoryManager->deleteItem(resultItem);
		std::cout << "You have deleted " << delItemName << ".";
	}
}
void deleteItemsByCategory()
{
	std::string searchKey;
	std::vector<Item*> resultItemVector;
	std::cout << "Enter the Category: ";
	std::cin >> searchKey;
	resultItemVector = globalInventoryManager->getItemsByCategory(searchKey);
	if (resultItemVector.size() == 0)
		std::cout << "No items found" << std::endl;
	else
	{
		std::vector<Item*>::iterator rivit;
		for (rivit = resultItemVector.begin(); rivit != resultItemVector.end(); ++rivit)
		{
			(*rivit)->printItem();
			std::cout << std::endl;
		}
		std::cout << "Are you sure you want to delete all the items of " << searchKey << "? y/n" << std::endl;
		std::string input;
		std::cin >> input;
		if (input == "y")
		{
			std::vector<Item*>::iterator iit;
			for (iit = resultItemVector.begin(); iit != resultItemVector.end(); iit++)
				globalInventoryManager->deleteItem(*iit);
		}
	}
}
void deleteAllItems()
{
	std::string input;
	std::vector<Item*> resultItemVector;
	std::cout << "Are you sure you want to delete all the items in the inventory? y/n";
	std::cin >> input;
	if (input == "y")
	{
		resultItemVector = globalInventoryManager->getAllItems();
		std::vector<Item*>::iterator iit;
		for (iit = resultItemVector.begin(); iit != resultItemVector.end(); iit++)
			globalInventoryManager->deleteItem(*iit);
	}
}
void deleteItem()
{
	char choice;
	std::cout << "Would you like to delete one item or all items of a category or all items in the inventory? (enter 0 to go back)" << std::endl;
	std::cout << "1. One Item" << std::endl;
	std::cout << "2. All Items of a Category" << std::endl;
	std::cout << "3. All Items in the Inventory" << std::endl;
	std::cin >> choice;
	switch (choice)
	{
	case '0': return;
		break;
	case '1': deleteOneItem();
		break;
	case '2': deleteItemsByCategory();
		break;
	case '3': deleteAllItems();
		break;
	default:
		std::cout << "Invalid Character" << std::endl;
		return;
	}
}
void loanItem()
{
	LoanableItem* resultItem = loanableItemSelector("loan");
	if (!resultItem) return; //if null, return
	std::cout << std::endl << "Are you sure you want to " << (resultItem->isLoaned()?"return":"loan") << " the item above? y/n" << std::endl;
	std::string input;
	std::cin >> input;
	if (input == "y")
	{
		resultItem->toggleLoan();
		std::cout << "You have " << (resultItem->isLoaned() ? "loaned " : "returned ") << resultItem->getName() << "." << std::endl << std::endl << std::endl;
		resultItem->printItem();
	}
}
void repeatConfirmation(void (*func)(), std::string promptMessage)
{

	char repeat = 'y';
	do
	{
		system("cls");
		func();
		std::cout << promptMessage << std::endl;
		std::cin >> repeat;
		repeat = tolower(repeat);
	} while (repeat == 'y');
}

int main()
{
	bool testing = false;
	if (!testing)
	{
		globalInventory = new Inventory();
		globalInventoryManager = new InventoryManager(*globalInventory);
		addItem("Excalibur", "category1,category2", true);
		addItem("Elucidator", "category1,category2", true);
		addItem("Dark Repulser", "category2,category3", false);
		addItem("Lambent Light", "category2,category3", false);
		char choice = NULL;
		do
		{
			std::cout << "Welcome to EquipmentLoanSystem v1.0 by David Choo :)" << std::endl;
			std::cout << "What would you like to do?" << std::endl;
			std::cout << "1. Search for an existing equipment (working, no error handling)" << std::endl;
			std::cout << "2. Add a new equipment (working, no error handling)" << std::endl;
			std::cout << "3. Edit an existing equipment (not yet)" << std::endl;
			std::cout << "4. Delete an existing equipment (not yet)" << std::endl;
			std::cout << "5. Loan/Return an existing equipment (not yet)" << std::endl;
			std::cout << "0. Exit (working)" << std::endl;
			std::cin >> choice;
			//std::cout << "--------------------------------" << std::endl;
			switch (choice)
			{
			case '0':
				break;
			case '1':
				repeatConfirmation(searchItem, "Search another item? y/n");
				break;
			case '2':
				repeatConfirmation(addItem, "Add another item? y/n");
				break;
			case '3':
				repeatConfirmation(editItem, "Edit another item? y/n");
				break;
			case '4':
				repeatConfirmation(deleteItem, "Delete another item? y/n");
				break;
			case '5':
				repeatConfirmation(loanItem, "Loan/Return another item? y/n");
				break;
			default:
				std::cout << "Invalid character" << std::endl;
			}
			system("cls");

		} while (choice != '0');
		//TODO implement Are you sure you want to exit
		//std::cout << "Bye bye (Enter again to exit)" << std::endl;
		//std::cin.ignore(); //for some reason, it needs 2 cin.ignore()
		//std::cin.ignore();
	}
	
	else
	{
		// test codes here
		/*f("uno");
		f("quattro");
		cin.ignore();*/
	}
	return 0;
}