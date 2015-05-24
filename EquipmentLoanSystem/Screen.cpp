#include <iostream>
#include <string>

using namespace std;

class Screen
{
public:
	Screen(Screen &prevScreen)
	{
		Screen::prevScreen = &prevScreen;
	}
private:
	Screen *prevScreen;
};