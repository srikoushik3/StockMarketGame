#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include "Gamerun.h"
#include <memory>

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(std::shared_ptr<GameRun>, QWidget *parent = 0);
    ~Graph();

private:
    void makePlot();
    Ui::Graph *ui;
    std::shared_ptr<GameRun> gsm;
};

#endif // GRAPH_H
