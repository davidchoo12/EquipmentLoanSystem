//*************************************************************
// Author: David Choo
// 
// class LoanableItem.h
// This class inherits the Item class representing items that are loanable.
//*************************************************************
#pragma once

#include <string>
#include "Item.h"

class LoanableItem : public Item
{
public:
	//Parameterised constructor
	//Postcondition: the parent's parameterised constructor is used, local variables are initialised
	LoanableItem(std::string name, std::vector<std::string*> &category);

	//Overiden print function from parent
	//Postcondition: the loanable item's details are printed in the same format as the parent's print function
	void printItem() const;

	//Function to toggle the onLoan variable and update the loanCount
	//Postcondition: onLoan is reversed, loanCount is incremented if the item is being loaned
	void toggleLoan();

	//Function to check if the item is being loaned
	//Postcondition: onLoan is returned
	bool isLoaned() const;
private:
	bool onLoan;
	int loanCount;
};