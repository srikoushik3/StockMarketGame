#include "NewGameUI.h"
#include "ui_NewGameUI.h"
#include "Managers/GameStateManager.h"
#include <fstream>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <memory>
#include <sstream>
#include "libs/json.hpp"
#include "GamerunUI.h"

using json = nlohmann::json;

using namespace std;

/* 
 * Parameters   : Shared pointer to GameStateManager and pointer to QWidget
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it sets up the new game settings window
 *    and displays default values for the fields displayed and also creates a
 *    shared pointer to NewGameState.
 */
NewGameFileManager::NewGameFileManager(shared_ptr<GameStateManager> gsm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameFileManager),
    daysPerTurn(0), totalDays(0), stocksFileName("stocks.json")
{
    //Set Labels to 0
    ui->setupUi(this);
    ui->daysLbl->setText("0");
    ui->totalDaysLbl->setText("0");
    ui->errorLabel->setText("");
    ui->usernameLbl->setText("");
    this->gsm = make_shared<NewGameState>(gsm);
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this destructor is invoked it simply deletes the UI component.
 */
NewGameFileManager::~NewGameFileManager()
{
    delete ui;
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it saves the days per turn and updates
 *    the display text accordingly.
 */
void NewGameFileManager::on_daysPerTurnBtn_clicked()
{
    daysPerTurn = QInputDialog::getInt(this, "Days Per Turn", "Enter Days Per Turn");
    ui->daysLbl->setText(QString::number(daysPerTurn));
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it saves the total days and updates
 *    the display text accordingly.
 */
void NewGameFileManager::on_totalDaysBtn_clicked()
{
    totalDays = QInputDialog::getInt(this, "Total Days", "Enter Total Days");
    ui->totalDaysLbl->setText(QString::number(totalDays));
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it prompts the user for stocks file.
 */
void NewGameFileManager::on_importStocksBtn_clicked()
{
    stocksFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Json File(*.json)").toStdString();
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it allows users to input their user names.
 */
void NewGameFileManager::on_usernameBtn_clicked()
{
    string usernameStr = QInputDialog::getText(this, "Usernames", "Enter Usernames (Comma Seperated)").toStdString();
    stringstream stream(usernameStr);
    string word;
    this->usernames.clear();
    //Adds comma seperated usernames to usernames vector
    while( getline(stream, word, ',') ){
        this->usernames.emplace_back(word);
    }
    ui->usernameLbl->setText(QString::fromStdString(usernameStr));
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the createStocksFromFile method to
 *    initialize the stocks and calls the createUsers method to initialize the
 *    users for the new game. Finally, it hide this window and moves to the
 *    actual game play window.
 */
void NewGameFileManager::on_submitBtn_clicked()
{
     // Make sure no fields are empty
    if(usernames.size() == 0 || daysPerTurn <= 0 || totalDays <= 0 || stocksFileName == ""){
        ui->errorLabel->setText("Please Enter a Value for All Fields");
        return;
    }
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Sumbit", "Are you Sure You Want to Submit?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        std::ifstream ifs(stocksFileName);
        json stocksJson;
        ifs >> stocksJson;
        this->gsm->createStocksFromFile(stocksJson);
        this->gsm->createUsers(usernames);
        gamerun gr(gsm, daysPerTurn, totalDays);
        this->hide();
        gr.setModal(true);
        gr.exec();
    }
}
