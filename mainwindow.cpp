#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgamefilemanager.h"
#include "gamerun.h"

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

void MainWindow::on_pushButton_clicked()
{
    gamerun fm;
    this->hide();
    fm.setModal(true);
    fm.exec();
}

