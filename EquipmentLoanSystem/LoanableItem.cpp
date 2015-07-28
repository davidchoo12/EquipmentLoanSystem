#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include "LoanableItem.h"
using namespace std;

LoanableItem::LoanableItem(string name, std::vector<std::string*> &category) : Item(name, category)
{
	LoanableItem::onLoan = false;
	LoanableItem::loanCount = 0;
}
void LoanableItem::printItem() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 250);
	f((LoanableItem::name + " (Loanable)").c_str());
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "Categories: ";
	LoanableItem::itemCategories->displayAll();
	std::cout << "Time Created: " << LoanableItem::timeCreated << std::endl;
	std::cout << "On Loan: " << (LoanableItem::onLoan? "true" : "false") << std::endl;
	std::cout << "Times Loaned: " << LoanableItem::loanCount << std::endl;
}

void LoanableItem::toggleLoan()
{
	LoanableItem::onLoan = !LoanableItem::onLoan;
	if (onLoan) loanCount++;
}
bool LoanableItem::isLoaned() const
{
	return onLoan;
}