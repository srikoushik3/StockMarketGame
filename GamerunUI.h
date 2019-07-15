#ifndef GAMERUN_H
#define GAMERUN_H

#include <QDialog>
#include "GameStateManager.h"
#include "Gamerun.h"
#include <memory>

namespace Ui {
class gamerun;
}

class gamerun : public QDialog
{
    Q_OBJECT

public:
    explicit gamerun(std::shared_ptr<GameStateManager>, int, int, QWidget *parent = 0);
    ~gamerun();

private slots:
    void on_buySellBtn_clicked();

    void on_buySubmitBtn_clicked();

    void on_sellSubmitBtn_clicked();
    void on_skipBtn_clicked();

    void on_saveGameBtn_clicked();

private:
    Ui::gamerun *ui;
    std::string stockName;
    void updateStockDropdown();
    void updateUserStockTable();
    void updateUserInformation();
    std::string getMonetaryFloat(float);
    int numShares;
    std::shared_ptr<GameRun> gsm;
};

#endif // GAMERUN_H
