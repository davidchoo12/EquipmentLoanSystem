#include <string>
#include "Item.h"
using namespace std;

class LoanableItem : public Item
{
public:
	LoanableItem(string name, std::vector<std::string*> &category);
	void printItem() const;
	void toggleLoan();
	bool isLoaned() const;
private:
	bool onLoan; //to be used
	int loanCount;
};