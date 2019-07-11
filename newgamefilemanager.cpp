#include "newgamefilemanager.h"
#include "ui_newgamefilemanager.h"
#include <fstream>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

NewGameFileManager::NewGameFileManager(QWidget *parent) :
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
}

NewGameFileManager::~NewGameFileManager()
{
    delete ui;
}

void NewGameFileManager::on_daysPerTurnBtn_clicked()
{
    // Save days per turn
    daysPerTurn = QInputDialog::getInt(this, "Days Per Turn", "Enter Days Per Turn");
    ui->daysLbl->setText(QString::number(daysPerTurn));
}

void NewGameFileManager::on_totalDaysBtn_clicked()
{
     // Save total days
    totalDays = QInputDialog::getInt(this, "Total Days", "Enter Total Days");
    ui->totalDaysLbl->setText(QString::number(totalDays));
}

void NewGameFileManager::on_importStocksBtn_clicked()
{
    // Promt user for stocks file
    stocksFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Json File(*.json)").toStdString();
}

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
        QApplication::quit();
    }
}

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
