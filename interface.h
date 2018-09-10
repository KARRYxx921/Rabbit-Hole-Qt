#ifndef INTERFACE_H
#define INTERFACE_H

#include <QMainWindow>
#include "interface_menu.h"
#include <QPoint>
#include "server.h"

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);
    ~Interface();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private slots:
    void on_table1_clicked();

    void on_table2_clicked();

    void on_table3_clicked();

    void on_table4_clicked();

    void on_table5_clicked();

    void on_table6_clicked();

    void on_table7_clicked();

    void on_table8_clicked();

    void on_table9_clicked();

private slots:
    //是否有顾客
    //void clientSignal(int a);
    //void clientSlot(int a);

    //新顾客上桌
    void clientontable(int num, int table);//编号，桌号

    //是否需要服务
    void serverSlot(int table);//桌号

    //点菜情况
    void orderSlot(int table, QString menuorder);//桌号，菜品

    //顾客离开
    void slotclientleave(int table);//桌号

    void on_action1_triggered();

    void on_action2_triggered();

    //显示时间
    void timeShow();

private slots:
    void iSlot(QString array, int table);


private:

    //和服务器的连接
    Server *m_server;

    //通信的相关信息
    int m_port;

    Ui::Interface *ui;

    //各桌菜单
    QString m_menu1;
    QString m_menu2;
    QString m_menu3;
    QString m_menu4;
    QString m_menu5;
    QString m_menu6;
    QString m_menu7;
    QString m_menu8;
    QString m_menu9;
    
    //上菜情况对应str
    QString me1;
    QString me2;
    QString me3;
    QString me4;
    QString me5;
    QString me6;
    QString me7;
    QString me8;
    QString me9;

    QPoint m_offset;

};

#endif // INTERFACE_H
