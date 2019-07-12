#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamestatebase.h"
#include "newgamefilemanager.h"
#include <memory>

using namespace std;

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
    shared_ptr<GameStateBase> gsm = make_shared<GameStateBase>();
    NewGameFileManager fm(gsm);
    this->hide();
    fm.setModal(true);
    fm.exec();
}

