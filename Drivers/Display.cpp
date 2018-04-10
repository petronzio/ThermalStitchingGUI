#include <iostream>
#include "Display.h"

Display::Display()
{
	// TODO Auto-generated constructor stub

}

Display::~Display()
{
	// TODO Auto-generated destructor stub
}

bool Display::Initialize (void)
{
	return true;
}

bool Display::ProcessCommand (const char command [], int size)
{
    //# Use command to avoid warning for now.
    if (command [0] == command [0])
    {}

	if (size == 11)
	{
        std::cout << "Display Display\n";
        return true;
	}

    return false;
}
