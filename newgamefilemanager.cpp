#include "newgamefilemanager.h"
#include "ui_newgamefilemanager.h"
#include <fstream>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

NewGameFileManager::NewGameFileManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameFileManager),
    numUsers(0), daysPerTurn(0), totalDays(0), stocksFileName("stocks.json")
{
    ui->setupUi(this);
    ui->numUsersLbl->setText("0");
    ui->daysLbl->setText("0");
    ui->totalDaysLbl->setText("0");
    ui->errorLabel->setText("");
}

NewGameFileManager::~NewGameFileManager()
{
    delete ui;
}

void NewGameFileManager::on_numUsersBtn_clicked()
{
    numUsers = QInputDialog::getInt(this, "Number of Users", "Enter Number of Users");
    ui->numUsersLbl->setText(QString::number(numUsers));
}

void NewGameFileManager::on_daysPerTurnBtn_clicked()
{
    daysPerTurn = QInputDialog::getInt(this, "Days Per Turn", "Enter Days Per Turn");
    ui->daysLbl->setText(QString::number(daysPerTurn));
}

void NewGameFileManager::on_totalDaysBtn_clicked()
{
    totalDays = QInputDialog::getInt(this, "Total Days", "Enter Total Days");
    ui->totalDaysLbl->setText(QString::number(totalDays));
}

void NewGameFileManager::on_importStocksBtn_clicked()
{
    stocksFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Json File(*.json)").toStdString();
}

void NewGameFileManager::on_submitBtn_clicked()
{
    if(numUsers == 0 || daysPerTurn == 0 || totalDays == 0 || stocksFileName == ""){
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
