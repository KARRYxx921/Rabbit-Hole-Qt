#include "mainwindow.h"
#include "tablewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TableWidget tw;
    tw.show();
    w.show();

    return a.exec();
}
