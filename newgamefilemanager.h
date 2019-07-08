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
    void on_pushButton_clicked();

private:
    Ui::NewGameFileManager *ui;
};

#endif // NEWGAMEFILEMANAGER_H
