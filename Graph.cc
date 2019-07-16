#include "Graph.h"
#include "Gamerun.h"
#include <iostream>
#include <memory>
#include "ui_Graph.h"
#include <QVector>

using namespace std;

/* 
 * Parameters   : Shared pointer to GameRun and pointer to QWidget
 * Return Value : None
 * Description  : 
 *    When this contructor is invoked it does the set up for the graph UI
 *    and calls the makePlot method defined below.
 */
Graph::Graph(shared_ptr<GameRun> gsm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph),
    gsm(gsm)
{
    ui->setupUi(this);
    Graph::makePlot();
}

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this method is invoked it produces a graph plot with Profit Earned
 *    on the Y-axis and Number of Transactions on the X-axis.
 */
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

/* 
 * Parameters   : None
 * Return Value : None
 * Description  : 
 *    When this destructor is invoked it simply deletes the UI component.
 */
Graph::~Graph()
{
    delete ui;
}
