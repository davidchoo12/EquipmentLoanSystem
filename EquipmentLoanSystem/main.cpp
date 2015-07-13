#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Inventory.h"
#include "Category.h"
#include "Item.h"
#include <stdlib.h>
//#include <conio.h>

Inventory *globalInventory;

void searchItem()
{
	char repeat = 'y';
	do
	{
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
		case '0': goto repeatConfirmation;
			break;
		case '1':
			std::cout << "Enter the Item name: ";
			std::cin >> searchKey;
			resultItemVector = globalInventory->getItemsByName(searchKey);
			break;
		case '2':
			std::cout << "Enter the Category: ";
			std::cin >> searchKey;
			resultItemVector = globalInventory->getItemsByCategory(searchKey);
			break;
		case '3': resultItemVector = globalInventory->getAllItems();
			break;
		default:
			std::cout << "Invalid Char" << std::endl;
			goto repeatConfirmation;
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
		
		repeatConfirmation:
		std::cout << "Search another item again? y/n" << std::endl;
		std::cin >> repeat;
		repeat = tolower(repeat);
	} while (repeat == 'y');
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
{
	char repeat = 'y';
	do
	{
		std::string nameInput;
		std::string categoryInput;
		std::cout << "Please enter item details" << std::endl;
		std::cout << "Name (without spaces, not working with spaces yet) (enter 0 to go back): ";
		std::cin >> nameInput;
		if (nameInput == "0") goto repeatConfirmation;
		std::cout << "Category: (use commas to delimit multiple values, no spaces in after commas)" << std::endl;
		std::cin >> categoryInput;
		char confirm;
		std::cout << "Are you sure? y/n" << std::endl;
		std::cin >> confirm;
		confirm = tolower(confirm);
		if (confirm == 'y')
		{
			std::vector<std::string*> *categoriesFromInput = categoriesStringToVector(categoryInput);
			std::vector<std::string*>::iterator cfiit;
			for (cfiit = categoriesFromInput->begin(); cfiit != categoriesFromInput->end(); ++cfiit) { *cfiit = globalInventory->decideWithAllCategories(*cfiit); }
			globalInventory->add(*(new Item(nameInput, *categoriesFromInput)));
			std::cout << "Item " << nameInput << " is added" << std::endl;
		}
		else if (confirm == 'n')
			std::cout << "You canceled adding " << nameInput << std::endl;
		else
			std::cout << "Invalid char" << std::endl;
		repeatConfirmation:
		std::cout << "Add another item again? y/n" << std::endl;
		std::cin >> repeat;
		repeat = tolower(repeat);
	} while (repeat == 'y');
}
void addItem(std::string itemName, std::string categories)
{
	std::vector<std::string*> *categoriesFromInput = categoriesStringToVector(categories);
	std::vector<std::string*>::iterator cfiit;
	for (cfiit = categoriesFromInput->begin(); cfiit != categoriesFromInput->end(); ++cfiit) { *cfiit = globalInventory->decideWithAllCategories(*cfiit); }
	globalInventory->add(*(new Item(itemName, *categoriesFromInput)));
}
void editItem()
{
	char repeat = 'y';
	do
	{
		char choice;
		std::cout << "Select the item you would like to edit. Do you want to search by Item name or Category or display all items? (enter 0 to go back)" << std::endl;
		std::cout << "1. Item name" << std::endl;
		std::cout << "2. Category" << std::endl;
		std::cout << "3. Display all Items" << std::endl;
		std::cin >> choice;
		std::vector<Item*> resultItemVector;
		std::string searchKey;
		std::vector<Item*>::iterator rivit;
		switch (choice)
		{
		case '0': goto repeatConfirmation;
			break;
		case '1':
			std::cout << "Enter the Item name: ";
			std::cin >> searchKey;
			resultItemVector = globalInventory->getItemsByName(searchKey);
			break;
		case '2':
			std::cout << "Enter the Category: ";
			std::cin >> searchKey;
			resultItemVector = globalInventory->getItemsByCategory(searchKey);
			break;
		case '3':
			resultItemVector = globalInventory->getAllItems();
			break;
		default:
			std::cout << "Invalid Character" << std::endl;
			goto repeatConfirmation;
		}
		if (resultItemVector.size() == 0)
			std::cout << "No items found" << std::endl;
		else
		{
			int counter = 0;
			for (rivit = resultItemVector.begin(); rivit != resultItemVector.end(); ++rivit)
			{
				std::cout << "Item " << counter << std::endl;
				(*rivit)->printItem();
				counter++;
			}
			std::cout << "Enter the number of the item you want to change or enter 0 to search again" << std::endl;
			std::cin >> choice;
			if (choice == '0') goto repeatConfirmation;
			else //unnecessary since if choice is 0, the following code wont run
			{
				int choiceInt = choice - '1';
				resultItemVector.at(choiceInt)->printItem();
				std::cout << "New name (enter 0 if you dont want to change) : ";
				std::string input;
				std::cin >> input;
				if (input != "0")
					resultItemVector.at(choiceInt)->setName(input);
				std::cout << "New categories (comma delimited, no spaces) (enter 0 if you dont want to change): " << std::endl;
				std::cin >> input;
				if (input != "0")
				{
					std::vector<std::string*> *categories = categoriesStringToVector(input);
					std::vector<std::string*>::iterator cit;
					for (cit = categories->begin(); cit != categories->end(); ++cit) { *cit = globalInventory->decideWithAllCategories(*cit); }
					resultItemVector.at(choiceInt)->setCategories(*categories);
				}
				resultItemVector.at(choiceInt)->printItem();
			}
			resultItemVector.clear();
		}

	repeatConfirmation:
		std::cout << "Edit another item again? y/n" << std::endl;
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
		addItem("placeholder", "category1,category2");
		addItem("placeholder2", "category1,category2");
		char choice = NULL;
		do
		{
			std::cout << "Welcome to EquipmentLoanSystem v1.0 by David Choo :)" << std::endl;
			std::cout << "What would you like to do?" << std::endl;
			std::cout << "1. Search for an existing equipment (working, no error handling)" << std::endl;
			std::cout << "2. Add a new equipment (working, no error handling)" << std::endl;
			std::cout << "3. Edit an existing equipment (not yet)" << std::endl;
			std::cout << "4. Delete an existing equipment (not yet)" << std::endl;
			std::cout << "5. Loan an existing equipment (not yet)" << std::endl;
			std::cout << "0. Exit (working)" << std::endl;
			std::cin >> choice;
			std::cout << "--------------------------------" << std::endl;
			switch (choice)
			{
			case '1':
				searchItem();
				break;
			case '2':
				addItem();
				break;
			case '3':
				editItem();
				break;
			}
			system("cls");

		} while (choice != '0');
		//TODO implement Are you sure you want to exit
		//std::cout << "Bye bye (Enter again to exit)" << std::endl;
		//std::cin.ignore(); //for some reason, it needs 2 cin.ignore()
		//std::cin.ignore();
	}
	//
	//else
	//{
	//	// test codes here
	//	int key = 0;
	//	do
	//	{
	//		key = _getch();
	//		std::cout << key << std::endl;
	//	} while (key != 0);
	//}
	return 0;
}