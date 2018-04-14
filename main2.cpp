#include <iostream>
#include "Drivers/PanTilt.h"
#include "Drivers/Imager.h"
#include "Drivers/Display.h"
#include "Modules/Retriever.h"
#include "Modules/Stitcher.h"

PanTilt _panTilt;
Imager _imager;
Display _display;
Retriever _retriever;
//Stitcher _stitcher;

void DisplayMessage (std::string message)
{
	std::cout << message;
}

bool ProcessCommand (std::string input)
{
	const char *cstr = input.c_str();
	int length = input.length();
	if (length > 0 && cstr [0] == '$')
	{
		length--;

		if (length == 1 && cstr [1] == 'X')
            exit (0);
		if (length > 1 && cstr [1] == 'P' && cstr [2] == 'T')
            return _panTilt.ProcessCommand(cstr + 3, length - 2);	// Forward to PanTilt
		else if (length > 1 && cstr [1] == 'I' && cstr [2] == 'R')
            return _imager.ProcessCommand(cstr + 3, length - 2);	// Forward to Imager
		else if (length > 0 && cstr [1] == 'D')
            return _display.ProcessCommand(cstr + 2, length - 1);   // Forward to Display
        else if (length > 0 && cstr [1] == 'R')
            return _retriever.ProcessCommand (cstr + 2, length - 1);// Forward to Retriever
	}

    return false;
}

bool EvaluateInitialization (bool success)
{
	if (success)
		DisplayMessage ("Complete\n");
	else
		DisplayMessage ("Failed\n");

	return success;
}

bool InitializePanTilt ()
{
	DisplayMessage ("\tInitializing Pan/Tilt Driver\t\t");
	return EvaluateInitialization (_panTilt.Initialize ());
}

bool InitializeImager ()
{
    DisplayMessage ("\tInitializing Imager Driver\n");
	return EvaluateInitialization (_imager.Initialize ());
}

bool InitializeDisplay ()
{
    DisplayMessage ("\tInitializing Display Driver\t\t");
    return EvaluateInitialization (_display.Initialize ());
}

bool InitializeRetriever ()
{
	DisplayMessage ("\tInitializing Retrieving Module\t\t");

    // Retrieving module needs a reference to the PT Driver along with
    // the Imager Driver. Pass these in on initialization.
    return true; //EvaluateInitialization (_retriever.Initialize (_panTilt, _imager, _stitcher));
}

bool InitializeStitcher ()
{
	DisplayMessage ("\tInitializing Stitching Module\t\t");
    return true;// EvaluateInitialization (_stitcher.Initialize ());
}

int main2()
{
    // Print splash output.
    DisplayMessage ("Beginning Thermal Stitcher...\n");

	// Initialize Pan/Tilt Driver
	if (!InitializePanTilt ())
		return -1;

	// Initialize Imager Driver
    if (!InitializeImager ())
        return -1;

    // Initialize Display Driver
    if (!InitializeDisplay ())
		return -1;

    // Initialize Stitching Module
    if (!InitializeStitcher ())
        return -1;

	// Initialize Retrieving Module
	if (!InitializeRetriever ())
		return -1;

	// Begin an infinite loop that will utilize these modules.
	std::string input;
	while (true)
	{
		std::cin >> input;
        if (!ProcessCommand (input))
            std::cout << "Error Processing Command: " + input + "\n";
	}

    return 0;
}
