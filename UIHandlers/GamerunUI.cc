#include "GamerunUI.h"
#include "ui_GamerunUI.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <QInputDialog>
#include <QMessageBox>
#include "Exceptions/Exception.h"
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

using json = nlohmann::json;

/* 
 * Parameters   : shared pointer to GameStateManager, integer for days per turn, integer for total days and pointer to QWidget
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it sets up the game run window and other
 *    components such as the table, user information and dropdown menu.
 */
gamerun::gamerun(shared_ptr<GameStateManager> gsm, int daysPerTurn, int totalDays, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamerun),
    gsm(make_shared<GameRun>(gsm, daysPerTurn, totalDays))
{
    ui->setupUi(this);
    ui->buySellLbl->setText("");
    updateStockDropdown();
    this->gsm->attach(this);
    this->render();
}

void gamerun::render(){
    updateUserInformation();
    updateUserStockTable();
}

void gamerun::gameOver(){
    string winStr = "Game Over, Player: " + this->gsm->getWinningPlayer() + " won!";
    QMessageBox::information(this, tr("Game Over"), QString::fromStdString(winStr));
    QApplication::exit();
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the getAllAvailableStocks method to
 *    add all available stocks to the dropdown menu.
 */
void gamerun::updateStockDropdown(){
    vector<string> stocks = gsm->getAllAvailableStocks();
    for(string s: stocks){
        ui->stockDropdown->addItem(QString::fromStdString(s));
    }
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the getCurrentUserStockInfo method to
 *    retieve all user and stock information, which would then be accessed to
 *    populate the table.
 */
void gamerun::updateUserStockTable(){
    map<string, tuple<int, float, float, float>> userStocks = gsm->getCurrentUserStockInfo();
    ui->stocksTable->clear();
    ui->stocksTable->setColumnCount(5);
    ui->stocksTable->setRowCount(this->gsm->getAllAvailableStocks().size());
    ui->stocksTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList tableHeader;
    tableHeader << "Stock Name" << " # Shares Owned" << " Current Price" << " Average Purchase Price" << "Dividend";
    ui->stocksTable->setHorizontalHeaderLabels(tableHeader);
    int rowCount = 0;
    for (const auto &p: userStocks)
    {
        ui->stocksTable->setItem(rowCount,0,new QTableWidgetItem(QString::fromStdString(p.first)));
        ui->stocksTable->setItem(rowCount,1,new QTableWidgetItem(QString::number(get<0>(p.second))));
        ui->stocksTable->setItem(rowCount,2,new QTableWidgetItem(QString::fromStdString(getMonetaryFloat(get<2>(p.second)))));
        ui->stocksTable->setItem(rowCount,3,new QTableWidgetItem(QString::fromStdString(getMonetaryFloat(get<1>(p.second)))));
        ui->stocksTable->setItem(rowCount,4,new QTableWidgetItem(QString::fromStdString(getMonetaryFloat(get<3>(p.second)))));
        rowCount++;
    }
}

/* 
 * Parameters   : Float f
 * Return Value : String type
 * Description  : 
 *    When this method is invoked it displays monetary values in $x.xx format.
 */
string gamerun::getMonetaryFloat(float f) {
    stringstream stream;
    stream << "$" << std::fixed << std::setprecision(2) << f;
    return stream.str();
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the getCurrentUserInformation method to
 *    retieve the current user's information, which would then be accessed to
 *    update the users progress on display.
 */
void gamerun::updateUserInformation(){
    string username;
    float cashBalance, profit;
    int currentDay;
    tie(username, cashBalance, profit, currentDay) = gsm->getCurrentUserInformation();
    ui->usernameLbl->setText(QString::fromStdString(username));
    stringstream stream;
    stream << "$" << std::fixed << std::setprecision(2) << cashBalance;
    ui->cashBalanceLbl->setText(QString::fromStdString(stream.str()));
    stream.str("");
    stream << "$" << std::fixed << std::setprecision(2) << profit;
    ui->profitsLbl->setText(QString::fromStdString(stream.str()));
    ui->currentDayLbl->setText(QString::number(currentDay));
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this destructor is invoked it simply deletes the UI component.
 */
gamerun::~gamerun()
{
    delete ui;
    this->gsm->detach(this);
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it prompts the user for number of shares
 *    they want to buy/sell.
 */
void gamerun::on_buySellBtn_clicked()
{
    numShares = QInputDialog::getInt(this, "Number of Shares", "Enter Number Of Shares");
    ui->buySellLbl->setText(QString::number(numShares));
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it prompts the user for number of shares to 
 *    buy and it will try to call the buyStockCurrentUser method to purchase a
 *    particular stock for the current user. If any errors, then an appropriate
 *    user/stock exception is thrown. Else success message is shown.
 */
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
    QMessageBox::information(this, tr("Success"), tr("Success!"));
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it prompts the user for number of shares to 
 *    sell and it will try to call the sellStockCurrentUser method to sell a
 *    particular stock for the current user. If any errors, then an appropriate
 *    user/stock exception is thrown. Else success message is shown.
 */
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
    QMessageBox::information(this, tr("Success"), tr("Success!"));
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the skipNextDayForCurrentUser method
 *    to start new trading day for current user. Additionally it calls
 *    updateUserInformation and updateUserStockTable to update the user information
 *    and table after the user completes a day of trading.
 */
void gamerun::on_skipBtn_clicked()
{
    gsm->skipNextDayForCurrentUser();
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it calls the saveGameForAllStocks and
 *    saveGameForUsers method on GameStateManager to save all the user and
 *    stock information into a user.json and stocks.json file, respectively.
 */
void gamerun::on_saveGameBtn_clicked()
{
    try{
        json stocksJson = gsm->saveGameForAllStocks();
        json usersJson = gsm->saveGameForUsers();
        ofstream users("users.json");
        users << setw(4) << usersJson << endl;
        ofstream stocks("stocks.json");
        stocks << setw(4) << stocksJson << endl;
        QMessageBox::information(this, tr("Success"), tr("Saved Game Successfully!"));
    }catch(...){
        QMessageBox::information(this, tr("Error"), tr("Could not Save Game"));
    }
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it creates an instance of the Graph Class by
 *    passing the shared pointer to the GameStateManager as a parameter and
 *    calling the methods to set up the graph for the user's historical profit.
 */
void gamerun::on_profitHistoryBtn_clicked()
{
    Graph profitHistory(gsm);
    profitHistory.setModal(true);
    profitHistory.exec();
}

void gamerun::on_exitBtn_clicked()
{
    QApplication::exit();
}
