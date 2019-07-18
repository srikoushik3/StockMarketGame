 /*
  * File: GamerunUI.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the gamerun class which inherit from
  *   the QDialog Class. This class is responsible for establishing the link
  *   between the Game Run Frontend and Backend by controlling actions of
  *   various UI components, such as buttons and dropdown.
  */
#ifndef GAMERUN_H
#define GAMERUN_H

#include <QDialog>
#include "Managers/GameStateManager.h"
#include "Managers/Gamerun.h"
#include "Observer.h"
#include <memory>

namespace Ui {
class gamerun;
}

class gamerun : public QDialog, public Observer
{
    Q_OBJECT

public:
    explicit gamerun(std::shared_ptr<GameStateManager>, int, int, QWidget *parent = 0);
    void render() override;
    void gameOver() override;
    ~gamerun();

private slots:
    void on_buySellBtn_clicked();

    void on_buySubmitBtn_clicked();

    void on_sellSubmitBtn_clicked();
    void on_skipBtn_clicked();

    void on_saveGameBtn_clicked();    
    void on_profitHistoryBtn_clicked();

    void on_exitBtn_clicked();

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
