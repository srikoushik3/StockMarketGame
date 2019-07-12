#ifndef GAMERUN_H
#define GAMERUN_H

#include <QDialog>

namespace Ui {
class gamerun;
}

class gamerun : public QDialog
{
    Q_OBJECT

public:
    explicit gamerun(QWidget *parent = 0);
    ~gamerun();

private slots:
    void on_buySellBtn_clicked();

private:
    Ui::gamerun *ui;
    std::string stockName;
    void updateStockDropdown();
    int numShares;
};

#endif // GAMERUN_H
