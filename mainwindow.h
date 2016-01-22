#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QPushButton>
//#include <QtWebView/QtWebView>
#include "QWebView"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //bool eventFilter(QObject *obj, QEvent *event);
    MainWindow(QWidget *parent = 0);
    void open_url();
    void next_url();
    void back_url();
    void hide_menu();
    ~MainWindow();
    bool set_page(QString str, QString name);

private:
    void createMenuList();
    QPushButton *next, *back, *hide;
    QWidget *mainWidget;
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QTreeWidget *menuList;
    QWebView *browser;
};

void createConnectionSqlite();

#endif // MAINWINDOW_H
