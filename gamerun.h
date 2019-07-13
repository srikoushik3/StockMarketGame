#ifndef GAMERUN_H
#define GAMERUN_H

#include <QDialog>
#include "gamestatemanager.h"
#include "newgamestate.h"
#include <memory>

namespace Ui {
class gamerun;
}

class gamerun : public QDialog
{
    Q_OBJECT

public:
    explicit gamerun(std::shared_ptr<GameStateManager>, QWidget *parent = 0);
    ~gamerun();

private slots:
    void on_buySellBtn_clicked();

private:
    Ui::gamerun *ui;
    std::string stockName;
    void updateStockDropdown();
    int numShares;
    std::shared_ptr<NewGameState> gsm;
};

#endif // GAMERUN_H
