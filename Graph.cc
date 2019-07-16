#include "Graph.h"
#include "Gamerun.h"
#include <iostream>
#include <memory>
#include "ui_Graph.h"
#include <QVector>

using namespace std;

Graph::Graph(shared_ptr<GameRun> gsm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph),
    gsm(gsm)
{
    ui->setupUi(this);
    Graph::makePlot();
}

void Graph::makePlot(){
    vector<float> histProfitsF = gsm->getHistoricalUserProfits();
    vector<double> histProfitsD(histProfitsF.begin(), histProfitsF.end());
    QVector<double> y = QVector<double>::fromStdVector(histProfitsD), x(histProfitsD.size());
    std::iota(x.begin(), x.end(), 0);
    // create graph and assign data to it:
    ui->returnsGraph->addGraph();
    ui->returnsGraph->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->returnsGraph->xAxis->setLabel("Transaction #");
    ui->returnsGraph->yAxis->setLabel("Profit Earned");
    // set axes ranges, so we see all data:
    ui->returnsGraph->xAxis->setRange(0, x.size());
    cout << gsm->getMinProfit() << " " << gsm->getMaxProfit() << endl;
    ui->returnsGraph->yAxis->setRange(gsm->getMinProfit(), gsm->getMaxProfit());
    ui->returnsGraph->replot();
}



Graph::~Graph()
{
    delete ui;
}
