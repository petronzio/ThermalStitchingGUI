#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Modules/Retriever.h"
#include <QFile>
#include <QDir>
#include <QString>
#include <iostream>
#include <thread>
#include "Drivers/PanTilt.h"
#include "Drivers/Imager.h"
#include "Modules/Stitcher.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void on_startButton_clicked();

    void on_resetButton_clicked();

};

#endif // MAINWINDOW_H
