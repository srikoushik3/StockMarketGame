#include "gamerun.h"
#include "ui_gamerun.h"
#include <iostream>
#include <vector>
#include <QInputDialog>
#include <QMessageBox>
#include "Exception.h"

using namespace std;

gamerun::gamerun(shared_ptr<GameStateManager> gsm, int daysPerTurn, int totalDays, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamerun),
    gsm(make_shared<GameRun>(gsm, daysPerTurn, totalDays))
{
    ui->setupUi(this);
    ui->buySellLbl->setText("");
    updateStockDropdown();
    updateUserInformation();
    updateUserStockTable();
}

void gamerun::updateStockDropdown(){
    vector<string> stocks = gsm->getAllAvailableStocks();
    for(string s: stocks){
        ui->stockDropdown->addItem(QString::fromStdString(s));
    }
}

void gamerun::updateUserStockTable(){
    map<string, tuple<int, float, float>> userStocks = gsm->getCurrentUserStockInfo();
    ui->stocksTable->clear();
    ui->stocksTable->setColumnCount(4);
    ui->stocksTable->setRowCount(this->gsm->getAllAvailableStocks().size());
    ui->stocksTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList tableHeader;
    tableHeader << "Stock Name" << " # Shares Owned" << " Current Price" << " Average Purchase Price";
    ui->stocksTable->setHorizontalHeaderLabels(tableHeader);
    ui->stocksTable->setRowCount(this->gsm->getAllAvailableStocks().size());
    int rowCount = 0;
    for (const auto &p: userStocks)
    {
        ui->stocksTable->setItem(rowCount,0,new QTableWidgetItem(QString::fromStdString(p.first)));
        ui->stocksTable->setItem(rowCount,1,new QTableWidgetItem(QString::number(get<0>(p.second))));
        ui->stocksTable->setItem(rowCount,2,new QTableWidgetItem(QString::number(get<2>(p.second))));
        ui->stocksTable->setItem(rowCount,3,new QTableWidgetItem(QString::number(get<1>(p.second))));
        rowCount++;
    }
}



void gamerun::updateUserInformation(){
    string username;
    float cashBalance, profit;
    int currentDay;
    tie(username, cashBalance, profit, currentDay) = gsm->getCurrentUserInformation();
    ui->usernameLbl->setText(QString::fromStdString(username));
    ui->cashBalanceLbl->setText(QString::number(cashBalance));
    ui->profitsLbl->setText(QString::number(profit));
    ui->currentDayLbl->setText(QString::number(currentDay));
}

gamerun::~gamerun()
{
    delete ui;
}

void gamerun::on_buySellBtn_clicked()
{
    // Prompt user for number of shares they want to buy/sell shares from
    numShares = QInputDialog::getInt(this, "Number of Shares", "Enter Number Of Shares");
    ui->buySellLbl->setText(QString::number(numShares));
}

void gamerun::on_buySubmitBtn_clicked()
{
    // Buy Stock
    stockName = ui->stockDropdown->currentText().toStdString();
    cout << stockName << endl;
    if(numShares <= 0 || stockName == ""){
        QMessageBox::information(this, tr("Error"), tr("Enter Valid Stock/# of Shares"));
        return;
    }
    try{
        gsm->buyStockCurrentUser(numShares, stockName);
    }catch(UserException e){
        QMessageBox::information(this, tr("Error"), tr(e.what()));
        return;
    }catch(StockException e){
        QMessageBox::information(this, tr("Error"), tr(e.what()));
        return;
    }
    updateUserInformation();
    updateUserStockTable();
    QMessageBox::information(this, tr("Success"), tr("Success!"));
}

void gamerun::on_sellSubmitBtn_clicked()
{
    // Sell Stock
    stockName = ui->stockDropdown->currentText().toStdString();
    cout << stockName << endl;
    if(numShares <= 0 || stockName == ""){
        QMessageBox::information(this, tr("Error"), tr("Enter Valid Stock/# of Shares"));
        return;
    }
    try{
        gsm->sellStockCurrentUser(numShares, stockName);
    }catch(UserException e){
        QMessageBox::information(this, tr("Error"), tr(e.what()));
        return;
    }catch(StockException e){
        QMessageBox::information(this, tr("Error"), tr(e.what()));
        return;
    }
    updateUserInformation();
    updateUserStockTable();
    QMessageBox::information(this, tr("Success"), tr("Success!"));
}

void gamerun::on_skipBtn_clicked()
{
    gsm->skipNextDayForCurrentUser();
    updateUserInformation();
    updateUserStockTable();
}
