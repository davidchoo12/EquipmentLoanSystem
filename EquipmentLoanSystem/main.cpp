//There was some issue with the stack size limit that the app throws an exception whenever the app is closed
//I configured the stack size to be 10MB instead of the default 1MB and it resolves the issue

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include "InventoryManager.h"
#include "Inventory.h"
#include "Category.h"
#include "Item.h"
#include <stdlib.h>
#include <Windows.h>
#include <fstream>

Inventory *globalInventory;
InventoryManager *globalInventoryManager;
static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //for colours
//colour codes:
//7 grey on black (original)
//15 white on black
//10 green on black
//12 red on black

//helper method to get character within the applicableChars (error handling)
char getValidatedChar(std::string applicableChars)
{
	char c;
	std::string input;
	std::stringstream ss;
	std::getline(std::cin, input);
	ss << input;
	bool canConvert, isApplicable;
	canConvert = bool(ss >> c);
	isApplicable = !(applicableChars.find(c) == std::string::npos);
	while (!canConvert || !isApplicable)//while the input is not 1 character and the inputted char is not in the string, meaning its not valid
	{
		std::cout << "Invalid character, please enter either of these characters: ";
		std::string::iterator sit;
		for (sit = applicableChars.begin(); sit != applicableChars.end(); sit++)
			std::cout << *sit << (*sit == applicableChars.back() ? "" : ", ");
		std::cout << std::endl;
		std::getline(std::cin, input);
		ss = std::stringstream();
		ss << input;
		canConvert = bool(ss >> c);
		isApplicable = !(applicableChars.find(c) == std::string::npos);
	}
	return c;
}
//interface method to search item
void searchItem()
{
	char choice;
	std::cout << "Do you want to search by Item name or Category or display all items? (enter 0 to go back)" << std::endl;
	std::cout << "1. Item name" << std::endl;
	std::cout << "2. Category" << std::endl;
	std::cout << "3. Display all Items" << std::endl;
	choice = getValidatedChar("0123");
	std::vector<Item*> resultItemVector;
	std::string searchKey;
	switch (choice)
	{
	case '0': return;
		break;
	case '1':
		std::cout << "Enter the Item name: ";
		std::getline(std::cin, searchKey);
		resultItemVector = globalInventoryManager->getItemsByName(searchKey);
		break;
	case '2':
		std::cout << "Enter the Category: ";
		std::getline(std::cin, searchKey);
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
	}
}
//used to convert comma delimited strings to string vector
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
//interface method to add item
void addItem()
{
	std::string nameInput;
	std::string categoryInput;
	char isLoanable;
	char confirm;
	std::cout << "Please enter item details" << std::endl;
	std::cout << "Name (without spaces, not working with spaces yet) (enter 0 to go back): ";
	std::getline(std::cin, nameInput);
	if (nameInput == "0") return;
	std::cout << "Category: (use commas to delimit multiple values, no spaces in after commas)" << std::endl;
	std::getline(std::cin, categoryInput);
	std::cout << "Is the item loanable? y/n" << std::endl;
	isLoanable = getValidatedChar("yn");
	std::cout << "Are you sure? y/n" << std::endl;
	confirm = getValidatedChar("yn");
	if (confirm == 'y')
	{
		std::vector<std::string*> *categoriesFromInput = categoriesStringToVector(categoryInput);
		globalInventoryManager->addItem(nameInput, *categoriesFromInput, (isLoanable == 'y'));
		std::cout << "Item " << nameInput << " is added" << std::endl;
	}
	else if (confirm == 'n')
		std::cout << "You canceled adding " << nameInput << std::endl;
	else
		std::cout << "Invalid char" << std::endl;
}
//overloaded method to add item without interface
void addItem(std::string itemName, std::string categories, bool isLoanable)
{
	std::vector<std::string*> *categoriesFromInput = categoriesStringToVector(categories);
	globalInventoryManager->addItem(itemName, *categoriesFromInput, isLoanable);
}
//interface to select non loanable item
Item* itemSelector(std::string prompt)
{
	char choice;
	std::cout << "Select the item you would like to " << prompt << ". Do you want to search by Item name or Category or display all items? (enter 0 to go back)" << std::endl;
	std::cout << "1. Item name" << std::endl;
	std::cout << "2. Category" << std::endl;
	std::cout << "3. Display all Items" << std::endl;
	choice = getValidatedChar("123");
	std::vector<Item*> resultItemVector;
	std::string searchKey;
	std::vector<Item*>::iterator rivit;
	switch (choice)
	{
	case '0': return nullptr;
		break;
	case '1':
		std::cout << "Enter the Item name: ";
		std::getline(std::cin, searchKey);
		resultItemVector = globalInventoryManager->getItemsByName(searchKey);
		break;
	case '2':
		std::cout << "Enter the Category: ";
		std::getline(std::cin, searchKey);
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
		std::string input;
		const char* selection;
		int c;
		std::stringstream ss;
		bool validInput;
		do
		{
			std::getline(std::cin, input);
			selection = input.c_str();
			if (*selection == '0') return nullptr;
			else //unnecessary since if choice is 0, the following code wont run
			{
				ss << selection;
				validInput = bool(ss >> c) && (c >= 1 && c <= resultItemVector.size());
				if (validInput)
				{
					resultItemVector.at(--c)->printItem();
					return resultItemVector.at(c);
				}
				else
				{
					std::cout << "Please enter a number from the item list." << std::endl;
				}
				ss = std::stringstream(); //to clear the stringstream
			}
		} while (!validInput);
	}
	return nullptr; //unnecessary because code wont reach here but compiler claims "not all control paths return a value"
}
//interface to select loanable item
LoanableItem* loanableItemSelector(std::string prompt)
{
	const char* choice;
	std::cout << "Select the item you would like to " << prompt << ". Do you want to search by Item name or Category or display all items? (enter 0 to go back)" << std::endl;
	std::cout << "1. Item name" << std::endl;
	std::cout << "2. Category" << std::endl;
	std::cout << "3. Display all Items" << std::endl;
	std::string in;
	std::getline(std::cin, in);
	choice = in.c_str();
	std::vector<LoanableItem*> resultItemVector;
	std::string searchKey;
	std::vector<LoanableItem*>::iterator rivit;
	switch (*choice)
	{
	case '0': return nullptr;
		break;
	case '1':
		std::cout << "Enter the Item name: ";
		getline(std::cin, searchKey);
		resultItemVector = globalInventoryManager->getLoanableItemsByName(searchKey);
		break;
	case '2':
		std::cout << "Enter the Category: ";
		getline(std::cin, searchKey);
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
		std::string input;
		const char* selection;
		int c;
		std::stringstream ss;
		bool validInput;
		do
		{
			std::getline(std::cin, input);
			selection = input.c_str();
			if (*selection == '0') return nullptr;
			else //unnecessary since if choice is 0, the following code wont run
			{
				ss << selection;
				validInput = bool(ss >> c) && (c >= 1 && c <= resultItemVector.size());
				if (validInput)
				{
					resultItemVector.at(--c)->printItem();
					return resultItemVector.at(c);
				}
				else
				{
					std::cout << "Please enter a number from the item list." << std::endl;
				}
				ss = std::stringstream(); //to clear the stringstream
			}
		} while (!validInput);
	}
	return nullptr; //unnecessary because code wont reach here but compiler claims "not all control paths return a value"
}
//interface method to edit item
void editItem()
{
	Item* resultItem = itemSelector("edit");
	if (!resultItem) return; //if null, return
	std::cout << "New name (enter 0 if you dont want to change) : ";
	std::string input;
	std::getline(std::cin, input);
	if (input != "0")
		resultItem->setName(input);
	std::cout << "New categories (comma delimited, no spaces) (enter 0 if you dont want to change): " << std::endl;
	std::getline(std::cin, input);
	if (input != "0")
	{
		std::vector<std::string*> *categories = categoriesStringToVector(input);
		globalInventoryManager->editItemCategory(resultItem, *categories);
	}
	resultItem->printItem();
}
//sub interface to delete 1 item
void deleteOneItem()
{
	Item* resultItem = itemSelector("delete");
	if (!resultItem) return; //if null, return
	std::cout << "Are you sure you want to delete the item above? y/n" << std::endl;
	char input = getValidatedChar("yn");
	if (input == 'y')
	{
		std::string delItemName = resultItem->getName();
		globalInventoryManager->deleteItem(resultItem);
		std::cout << "You have deleted " << delItemName << "." <<std::endl;
	}
}
//sub interface to delete all items in a category
void deleteItemsByCategory()
{
	std::string searchKey;
	std::vector<Item*> resultItemVector;
	std::cout << "Enter the Category: ";
	std::getline(std::cin, searchKey);
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
		char input = getValidatedChar("yn");
		if (input == 'y')
		{
			std::vector<Item*>::iterator iit;
			for (iit = resultItemVector.begin(); iit != resultItemVector.end(); iit++)
				globalInventoryManager->deleteItem(*iit);
		}
		std::cout << "You have deleted all items of category " << searchKey << "." << std::endl;
	}
}
//sub interface to delete all items in the inventory
void deleteAllItems()
{
	char input;
	std::vector<Item*> resultItemVector;
	std::cout << "Are you sure you want to delete all the items in the inventory? y/n" << std::endl;
	input = getValidatedChar("yn");
	if (input == 'y')
	{
		resultItemVector = globalInventoryManager->getAllItems();
		std::vector<Item*>::iterator iit;
		for (iit = resultItemVector.begin(); iit != resultItemVector.end(); iit++)
			globalInventoryManager->deleteItem(*iit);
		std::cout << "You have deleted all items in the inventory." << std::endl;
	}
}
//interface to delete items
void deleteItem()
{
	char choice;
	std::cout << "Would you like to delete one item or all items of a category or all items in the inventory? (enter 0 to go back)" << std::endl;
	std::cout << "1. One Item" << std::endl;
	std::cout << "2. All Items of a Category" << std::endl;
	std::cout << "3. All Items in the Inventory" << std::endl;
	choice = getValidatedChar("123");
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
//interface to loan items
void loanItem()
{
	LoanableItem* resultItem = loanableItemSelector("loan");
	if (!resultItem) return; //if null, return
	std::cout << std::endl << "Are you sure you want to " << (resultItem->isLoaned()?"return":"loan") << " the item above? y/n" << std::endl;
	char input = getValidatedChar("yn");
	if (input == 'y')
	{
		resultItem->toggleLoan();
		std::cout << "You have " << (resultItem->isLoaned() ? "loaned " : "returned ") << resultItem->getName() << "." << std::endl << std::endl << std::endl;
		resultItem->printItem();
		std::cout << std::endl;
	}
}
//method for quitting confirmation loop
void repeatConfirmation(void (*func)(), std::string promptMessage)
{
	char repeat = 'y';
	do
	{
		system("cls");
		func();
		std::cout << promptMessage << std::endl;
		repeat = getValidatedChar("yn");
	} while (repeat == 'y');
}

//FILE IO
//method to load the saved items in file
void loadFromFile(std::string fileLocation)
{
	std::ifstream data(fileLocation);
	std::string line;
	if (data.is_open())
	{
		while (getline(data, line))
		{
			size_t pos = 0;
			std::string token;
			std::vector<std::string> *itemParams = new std::vector<std::string>();
			while ((pos = line.find(";")) != std::string::npos)
			{
				token = line.substr(0, pos);
				itemParams->push_back(token);
				//as each category is added, it is erased from the input string
				line.erase(0, pos + 1);
			}
			if (itemParams->size() == 3) //because there is only 3 params for addItem
				addItem(itemParams->at(0), itemParams->at(1), (itemParams->at(2) == "true"));
		}
		data.close();
	}
}
//method to save all items to file
void saveToFile()
{
	std::vector<Item*> allItems = globalInventoryManager->getAllItems();
	std::vector<Item*>::iterator aiit;
	std::ofstream data("data.txt", std::ofstream::out | std::ofstream::trunc);
	if (data.is_open())
	{
		for (aiit = allItems.begin(); aiit != allItems.end(); aiit++)
		{
			data << (*aiit)->getName() << ";";
			std::vector<std::string*> *categories = (*aiit)->getCategories().getCategoryVector();
			std::vector<std::string*>::iterator cit;
			for (cit = categories->begin(); cit != categories->end(); cit++)
			{
				data << **cit << (cit == categories->end() - 1 ? ";" : ",");
			}
			LoanableItem *li = dynamic_cast<LoanableItem*>(*aiit);
			//if (typeid(*ivit).name() == "class LoanableItem")
			if (li) //if the conversion succeed, li would not be null so add it to the result vector
				data << "true;";
			else
				data << "false;";
			data << std::endl;
		}
	}
}

//MAIN
int main()
{
	globalInventory = new Inventory();
	globalInventoryManager = new InventoryManager(*globalInventory);
	loadFromFile("data.txt");
	SetConsoleTextAttribute(hConsole, 15);
	char choice;
	char exitConfirm;
	do
	{
		std::cout << "Welcome to EquipmentLoanSystem v1.0 by David Choo :)" << std::endl;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1. Search for an existing equipment" << std::endl;
		std::cout << "2. Add a new equipment" << std::endl;
		std::cout << "3. Edit an existing equipment" << std::endl;
		std::cout << "4. Delete an existing equipment" << std::endl;
		std::cout << "5. Loan/Return an existing equipment" << std::endl;
		std::cout << "0. Exit" << std::endl;
		choice = getValidatedChar("123450");
		switch (choice)
		{
		case '0':
			system("cls");
			SetConsoleTextAttribute(hConsole, 252);
			std::cout << "Are you sure you want to exit? y/n" << std::endl;
			exitConfirm = getValidatedChar("yn");
			if (exitConfirm == 'y')
				saveToFile();
			else
			{
				choice = NULL;
				SetConsoleTextAttribute(hConsole, 15);
			}
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
	return 0;
}