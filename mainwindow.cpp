#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
   /* ui->diag->setText("Hello World");
    QPixmap dadpic ("/home/ubuntuvm/ThermalGUI/dad.jpg");
    ui->image->setPixmap(dadpic);
    ui->image->setScaledContents( true );
    ui->image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);*/
}

void MainWindow::on_resetButton_clicked()
{
    ui->diag->setText("");
    ui->image->clear();
}
