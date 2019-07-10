#ifndef NEWGAMEFILEMANAGER_H
#define NEWGAMEFILEMANAGER_H

#include <QDialog>

namespace Ui {
class NewGameFileManager;
}

class NewGameFileManager : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameFileManager(QWidget *parent = 0);
    ~NewGameFileManager();

private slots:

    void on_daysPerTurnBtn_clicked();

    void on_totalDaysBtn_clicked();

    void on_importStocksBtn_clicked();

    void on_submitBtn_clicked();

    void on_usernameBtn_clicked();

private:
    Ui::NewGameFileManager *ui;
    int daysPerTurn, totalDays;
    std::vector<std::string> usernames;
    std::string stocksFileName;
};

#endif // NEWGAMEFILEMANAGER_H
