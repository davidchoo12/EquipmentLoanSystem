#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Inventory.h"
#include "Category.h"
#include "Item.h"

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
		if (choice == '0')
			goto repeatConfirmation;
		else if (choice == '1')
		{
			std::string searchKey;
			std::cout << "Enter the Item name: ";
			std::cin >> searchKey;
			globalInventory->displaySearch(searchKey);
		}
		else if (choice == '2')
		{
			std::string searchKey;
			std::cout << "Enter the Category: ";
			std::cin >> searchKey;
			globalInventory->displaySearchByCategory(searchKey);
		}
		else if (choice == '3')
		{
			globalInventory->displayAll();
		}
		else
			std::cout << "Invalid Char" << std::endl;

		repeatConfirmation:
		std::cout << "Search another item again? y/n" << std::endl;
		std::cin >> repeat;
		repeat = tolower(repeat);
	} while (repeat == 'y');
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
			categoryInput += ","; // so that the last categoryInput can be obtained (just a simple workaround)
			size_t pos = 0;
			std::string *token;
			std::vector<std::string*> *categoriesFromInput = new std::vector<std::string*>();
			while ((pos = categoryInput.find(",")) != std::string::npos)
			{
				token = new std::string(categoryInput.substr(0, pos));
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
					categoriesFromInput->push_back(globalInventory->decideWithAllCategories(token));
				}
				cfiit = categoriesFromInput->begin();
				//as each category is added, it is erased from the input string
				categoryInput.erase(0, pos + 1);
			}
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
int main()
{
	globalInventory = new Inventory();
	char choice = NULL;
	std::cout << "Welcome to EquipmentLoanSystem v1.0 by David Choo :)" << std::endl;
	do
	{
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
		case '3':;
		}
		std::cout << std::endl;
		
	} while (choice != '0');
	//TODO implement Are you sure you want to exit
	std::cout << "Bye bye (Enter again to exit)" << std::endl;
	std::cin.ignore(); //for some reason, it needs 2 cin.ignore()
	std::cin.ignore();
	return 0;
}