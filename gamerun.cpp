#include "gamerun.h"
#include "ui_gamerun.h"
#include <vector>
#include <QInputDialog>

using namespace std;

gamerun::gamerun(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gamerun)
{
    ui->setupUi(this);
    ui->buySellLbl->setText("");
    ui->stockNameLbl->setText("");
    ui->stocksTable->setColumnCount(4);
    ui->stocksTable->setRowCount(100);
    ui->stocksTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList tableHeader;
    tableHeader << "Stock Name" << " # Shares Owned" << " Current Price" << " Average Purchase Price";
    ui->stocksTable->setHorizontalHeaderLabels(tableHeader);
    updateStockDropdown();
}

void gamerun::updateStockDropdown(){
    vector<string> test({"str1", "str2", "str3", "str4", "str5"});
    for(string s: test){
        ui->stockDropdown->addItem(QString::fromStdString(s));
    }
}

gamerun::~gamerun()
{
    delete ui;
}

void gamerun::on_buySellBtn_clicked()
{
    // Prompt user for stock name they want to buy/sell shares from
    numShares = QInputDialog::getInt(this, "Stock Name", "Enter Stock Name");
    ui->buySellLbl->setText(QString::number(numShares));
}
