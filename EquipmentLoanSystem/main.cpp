#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Inventory.h"
#include "Category.h"
#include "Item.h"
using namespace std;
Inventory *globalInventory;
Category *globalCategories;

void searchItem()
{

}




// for comparing objects pointed by pointers in a pointer vector
template <typename T>
struct pointer_values_equal
{
	const T *to_find;

	bool operator()(const T* other) const
	{
		return to_find->compare(*other) == 0;
	}
};

void addItem()
{
	string nameInput;
	string categoryInput;
	std::cout << std::endl << "Please enter item details" << std::endl;
	std::cout << "Name: ";
	//std::getline(std::cin, nameInput, '\n');
	std::cin >> nameInput;
	std::cout << "Category: (use commas to delimit multiple values)" << std::endl;
	//std::getline(std::cin, categoryInput);
	std::cin >> categoryInput;
	categoryInput += ",";
	size_t pos = 0;
	std::string *token;
	std::vector<std::string*> *categoriesFromInput = new std::vector<std::string*>();
	while ((pos = categoryInput.find(",")) != std::string::npos)
	{
		token = new std::string(categoryInput.substr(0, pos));
		//pointer_values_equal<string> eq = { token };
		std::vector<string*>::iterator gcit =
			find_if(
			globalCategories->getCategoryVector()->begin(),
			globalCategories->getCategoryVector()->end(),
			[&token](const std::string *p)
			{ return *token == *p; });
		std::vector<string*>::iterator cfiit =
			find_if(
			categoriesFromInput->begin(),
			categoriesFromInput->end(),
			[&token](const std::string *p)
			{ return *token == *p; });
		// if not in categoriesfrominput (not repetitive)
		if (cfiit == categoriesFromInput->end())
		{
			// if not found in globalCategories
			if (gcit == globalCategories->getCategoryVector()->end())
			{
				globalCategories->add(token);
				categoriesFromInput->push_back(token);
				std::cout << "added " << token << std::endl;
			}
			else //if found in global categories
			{
				categoriesFromInput->push_back(*gcit);
				std::cout << "added " << *gcit << " to categoriesfrominput" << std::endl;
			}
		}
		gcit = globalCategories->getCategoryVector()->begin();
		cfiit = categoriesFromInput->begin();
		//as each category is added, it is erased from the input string
		categoryInput.erase(0, pos + 1);
	}

	globalInventory->add(*(new Item(nameInput, *categoriesFromInput)));
}
int main()
{
	globalInventory = new Inventory();
	globalCategories = new Category();
	char choice = '0';
	while (choice != '5')
	{
		cout << "Welcome to EquipmentLoanSystem v1.0 by David Choo :)" << endl;
		cout << "What would you like to do?" << std::endl;
		cout << "1. Search for a new equipment" << std::endl;
		cout << "2. Add a new equipment" << std::endl;
		cout << "3. Edit an existing equipment" << std::endl;
		cout << "4. Delete an existing equipment" << std::endl;
		cout << "5. Exit" << std::endl;
		cin >> choice;
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
		globalInventory->displayAll();
		
	}
	cout << "Bye bye" << endl;
	cin.ignore();
	
	//Category *b;
	//b = new Category("cat1");
	//globalCategories->push_back(*b);
	//Item *a;
	//a = new Item("item a", "cat1");
	//std::vector<Category>::iterator it;
	//it = find(globalCategories->begin(), globalCategories->end(), *(new Category("")));
	//if (it != globalCategories->end())
	//	a->setCategory(*it);
	//else
	//{
	//	Category("cat1");
	//	//a->setCategory(*(Category::globalCategories->end()));
	//}
	//std::cout << a->getCategories()[0].getCategory() << std::endl;



	cin.ignore();
	return 0;
}