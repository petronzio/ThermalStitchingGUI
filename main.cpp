#include "mainwindow.h"
#include <QApplication>
#include "Modules/Stitcher.h"

Stitcher _stitcher;

bool InitializeStitcher (Ui::MainWindow *ui)
{
    //DisplayMessage ("\tInitializing Stitching Module\t\t");
    return _stitcher.Initialize(ui);// EvaluateInitialization (_stitcher.Initialize ());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    // Initialize Stitching Module
    if (!InitializeStitcher (w.ui))
        return -1;
    //test
    return a.exec();
}
