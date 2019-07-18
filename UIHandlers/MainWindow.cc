#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Managers/GameStateBase.h"
#include "NewGameUI.h"
#include "Managers/LoadGameState.h"
#include "GamerunUI.h"
#include <memory>
#include <fstream>
#include <iostream>

using namespace std;

/* 
 * Parameters   : Pointer to QWidget
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it does the UI set up for main window. 
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this destructor is invoked it simply deletes this UI component
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it means user has selected new game,
 *    thus we hide the main window and display the file manager for the
 *    new game where the user can select their game settings/files.
 */
void MainWindow::on_pushButton_clicked()
{
    shared_ptr<GameStateBase> gsm = make_shared<GameStateBase>();
    NewGameFileManager fm(gsm);
    this->hide();
    fm.setModal(true);
    fm.exec();
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it means user has selected load game,
 *    thus we hide the main window, automatically set the user and
 *    stock files saved from the previous game session, and display the
 *    game window.
 */
void MainWindow::on_loadGameBtn_clicked()
{
    shared_ptr<LoadGameState> gsm = make_shared<LoadGameState>(make_shared<GameStateBase>());
    ifstream ifs("stocks.json");
    json stocksJson, usersJson;
    ifs >> stocksJson;
    ifstream ufs("users.json");
    ufs >> usersJson;
    gsm->loadStocksFromFile(stocksJson);
    gsm->loadUsersFromFile(usersJson["users"]);
    gamerun gr(gsm, usersJson["daysPerTurn"], usersJson["totalDays"]);
    this->hide();
    gr.setModal(true);
    gr.exec();
}
