#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GameStateBase.h"
#include "NewGameUI.h"
#include "LoadGameState.h"
#include "GamerunUI.h"
#include <memory>
#include <fstream>

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


void MainWindow::on_loadGameBtn_clicked()
{
    shared_ptr<LoadGameState> gsm = make_shared<LoadGameState>(make_shared<GameStateBase>());
    ifstream ifs("stocks.json");
    json stocksJson, usersJson;
    ifs >> stocksJson;
    ifstream ufs("users.json");
    ufs >> usersJson;
    gsm->loadStocksFromFile(stocksJson);
    gsm->loadUsersFromFile(usersJson);
    gamerun gr(gsm, 10, 10);
    this->hide();
    gr.setModal(true);
    gr.exec();
}
