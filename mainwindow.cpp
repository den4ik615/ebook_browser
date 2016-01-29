#include "mainwindow.h"
#include "QWidget"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QTreeWidget"
#include "QTreeWidgetItem"
#include "QHeaderView"
#include <QtSql>
#include <QSqlError>
#include <QWebView>
#include <QLabel>
#include <QMouseEvent>
#include <QTreeWidgetItemIterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget;
    vlayout =new QVBoxLayout;
    hlayout = new QHBoxLayout;
    menuList = new QTreeWidget;
    //menuList->setColumnCount(1);
    menuList->setHeaderLabels(QStringList() << "ОГЛАВЛЕНИЕ");
    menuList->setWordWrap(true);
    menuList->setTextElideMode(Qt::ElideNone);
    menuList->setHeaderHidden(true);
    //menuList->header()->resizeSection(0, 300);
    menuList->setMaximumWidth(400);
    menuList->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));
    //menuList->headerView()->resizeSection(0 /*column index*/, 400 /*width*/);;
    //menuList->installEventFilter(this);
    connect(menuList,&QTreeWidget::itemClicked,this,&MainWindow::open_url);
    browser = new QWebView;
    //browser->load(QUrl("http://google.com/"));
    browser->show();
    setCentralWidget(mainWidget);
    hlayout->addWidget(menuList);
    hlayout->addWidget(browser);
    vlayout->addLayout(hlayout);
    QHBoxLayout *hlayout_2 = new QHBoxLayout;
    next = new QPushButton;
    back = new QPushButton;
    hide = new QPushButton;
    hide->setText("Скрыть меню");
    back->setText("Назад");
    next->setText("Вперед");
    connect(hide,&QPushButton::clicked,this,&MainWindow::hide_menu);
    connect(back,&QPushButton::clicked,this,&MainWindow::back_url);
    connect(next,&QPushButton::clicked,this,&MainWindow::next_url);
    hlayout_2->addWidget(hide);
    hlayout_2->addWidget(back);
    hlayout_2->addWidget(next);
    vlayout->addLayout(hlayout_2);
    mainWidget->setLayout(vlayout);
    createMenuList();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createMenuList()
{
    qDebug()<<"Users database";
    QLabel *label;
    QString str="select id, name from tema";
    QSqlQuery query(QSqlDatabase::database("SQLITE"));
    QSqlQuery query_2(QSqlDatabase::database("SQLITE"));
    QSqlQuery query_3(QSqlDatabase::database("SQLITE"));
    query.exec(str);
    QTreeWidgetItem *newItem;
    while(query.next())
    {
        query.value(1).toString();
        newItem = new QTreeWidgetItem(menuList);
        label = new QLabel;
        label->setWordWrap(true);
        label->setText(query.value(1).toString());
        menuList->setItemWidget(newItem,0,label);
        //newItem->setText(0,query.value(1).toString());

        QString str_2="select id, name from glava where tema = '%1'";
        str_2=str_2.arg(query.value(0).toString());
        query_2.exec(str_2);
        while(query_2.next())//формирование списка пользователей
        {
            query_2.value(0).toString();
            QTreeWidgetItem *item = new QTreeWidgetItem(newItem);
            QLabel *label_2 = new QLabel; ;
            label_2->setWordWrap(true);
            label_2->setText(query_2.value(1).toString());
            menuList->setItemWidget(item,0,label_2);

            QString str_3="select name from paragraf where glava = '%1'";
            str_3=str_3.arg(query_2.value(0).toString());
            query_3.exec(str_3);
            while(query_3.next())//формирование списка пользователей
            {
                qDebug()<<query_3.value(0).toString();
                QTreeWidgetItem *item_2 = new QTreeWidgetItem(item);
                QLabel *label_3 = new QLabel; ;
                label_3->setWordWrap(true);
                label_3->setText(query_3.value(0).toString());
                menuList->setItemWidget(item_2,0,label_3);
                //item->
                //item->setText(0,query_2.value(0).toString());
            }
        }
        //menuList->addItem(newItem);
    }
}

void MainWindow::open_url()
{
    QLabel* label = qobject_cast<QLabel*>(menuList->itemWidget(menuList->currentItem(),0));
    QString name=label->text();
    if(set_page("tema",name))
    {
        return;
    }
    if(set_page("glava",name))
    {
        return;
    }
    if(set_page("paragraf",name))
    {
        return;
    }
}

void MainWindow::hide_menu()
{
    if(!menuList->isHidden())
    {
        menuList->setHidden(true);
        hide->setText("Показать меню");
    }
    else
    {
        menuList->setHidden(false);
        hide->setText("Скрыть меню");
    }
}

void MainWindow::next_url()
{
    QTreeWidgetItemIterator it(menuList);
    while (*it) {
        //QTreeWidgetItem* currentItem = <QTreeWidgetItem*>(*it);
        if ( (*it) == menuList->currentItem())
        {
            qDebug()<<(*it);
            ++it;
            qDebug()<<(*it);
            //(*it)->setSelected(true);
            if((*it))
            {
                menuList->setCurrentItem((*it));
                menuList->setItemSelected((*it),true);
            }
            qDebug()<<"iterator";
            break;
        }
        ++it;
    }
    QLabel* label = qobject_cast<QLabel*>(menuList->itemWidget(menuList->currentItem(),0));
    QString name=label->text();
    if(set_page("tema",name))
    {
        return;
    }
    if(set_page("glava",name))
    {
        return;
    }
    if(set_page("paragraf",name))
    {
        return;
    }
}

void MainWindow::back_url()
{
    QTreeWidgetItemIterator it(menuList);
    while (*it) {
        //QTreeWidgetItem* currentItem = <QTreeWidgetItem*>(*it);
        if ( (*it) == menuList->currentItem())
        {
            qDebug()<<(*it);
            --it;
            qDebug()<<(*it);
            //(*it)->setSelected(true);
            if((*it))
            {
                menuList->setCurrentItem((*it));
                menuList->setItemSelected((*it),true);
            }
            qDebug()<<"iterator";
            break;
        }
        ++it;
    }
    QLabel* label = qobject_cast<QLabel*>(menuList->itemWidget(menuList->currentItem(),0));
    QString name=label->text();
    if(set_page("tema",name))
    {
        return;
    }
    if(set_page("glava",name))
    {
        return;
    }
    if(set_page("paragraf",name))
    {
        return;
    }
}

bool MainWindow::set_page(QString tabl, QString name)
{
    QString str="select id from %1 where name = '%2'";
    QSqlQuery query(QSqlDatabase::database("SQLITE"));
    str=str.arg(tabl).arg(name);
    query.exec(str);
    if (query.next()) {
        int i=query.value(0).toInt();
        str="select file from %1 where id = '%2'";
        str=str.arg(tabl).arg(i);
        query.exec(str);
        if (query.next()) {
            browser->setContent(query.value(0).toByteArray());
            browser->page()->settings()->setAttribute(QWebSettings::JavaEnabled, true);
            browser->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
            return true;
        }
    }
    return false;
}

/*bool MainWindow::eventFilter(QObject *obj, QEvent *event) //обработчик щелчка мыши по фотографии для расскрытия подробной информации
{
    QMouseEvent *mouse = (QMouseEvent *)event;//получаем событие мыши приводя тип события к событию мыши
    if(mouse->button()==Qt::LeftButton)
    {
        //infa(obj);
        qDebug()<<"жмяк";
        return true;
    }
    else {
        //qDebug()<<"жмяк";
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}*/

void createConnectionSqlite()
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE","SQLITE");
    qDebug()<<QString( QCoreApplication::applicationDirPath() + "/source.sqlite" );
    sdb.setDatabaseName(QString( QCoreApplication::applicationDirPath() + "/source.sqlite" ));
    if(!sdb.open())
    {
        qDebug()<<"Ошибка открытия базы данных";
    }
}
