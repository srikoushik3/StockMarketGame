 /*
  * File: MainWindow.h
  * 
  * Date: Spring 2019
  * Summary of File:
  *   This file contains code for the MainWindow class which inherits from
  *   the QMainWindow Class and is responsible for displaying the option to
  *   create new game and load previous game; thereby redirecting user to
  *   requested option via button push.
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_loadGameBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
