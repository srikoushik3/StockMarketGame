#include "newgamefilemanager.h"
#include "ui_newgamefilemanager.h"
#include <fstream>
#include <QFileDialog>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

NewGameFileManager::NewGameFileManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameFileManager)
{
    ui->setupUi(this);
}

NewGameFileManager::~NewGameFileManager()
{
    delete ui;
}

void NewGameFileManager::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "Json File(*.json)");
    std::ifstream ifs(filename.toStdString());
    json stocksJson;
    ifs >> stocksJson;
}
