#include "MainWindow.h"
#include <QApplication>

/* 
 * Parameters   : Integer argc and pointer to char argv
 * Return Value : Integer type
 * Description  : 
 *    When this method is invoked it does the set up for the application and
 *    displays the main window UI.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
