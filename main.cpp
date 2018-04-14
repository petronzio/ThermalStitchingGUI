#include "mainwindow.h"
#include <QApplication>
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
Stitcher _stitcher;

void DisplayMessage (std::string message)
{
    std::cout << message;
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
    return EvaluateInitialization (_retriever.Initialize (_panTilt, _imager, _stitcher));
}

bool InitializeStitcher (Ui::MainWindow *ui)
{
    //DisplayMessage ("\tInitializing Stitching Module\t\t");
    return EvaluateInitialization (_stitcher.Initialize(ui));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
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
    if (!InitializeStitcher (w.ui))
        return -1;
    // Initialize Retrieving Module
    if (!InitializeRetriever ())
        return -1;

    return a.exec();
}
