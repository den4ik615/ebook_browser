#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createConnectionSqlite();
    MainWindow w;
    w.show();

    return a.exec();
}
