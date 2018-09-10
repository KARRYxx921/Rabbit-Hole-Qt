#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QList>
#include "tcpclientsocket.h"
#include "aaaaaaa/tablewidget.h"


class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = 0, int port = 0);
    QList<TcpClientSocket*> tcpclientsocketlist;
    /*与数据库的有关函数
     * int neclienttobase() //数据库创建新顾客，并返回新顾客编号
     * int gettable(int num) //从数据库获取某编号（num）的桌号,若暂时不能上桌，还需排队则返回0
     * int getfront(int num) //从数据库获取某编号(num)的前方排队人数
     * void clientleavetobase(int table) //告诉数据库某桌（table）客人离开,变化表格
     * int getnewclient() //从数据库获取下一个可以上桌的顾客编号
     * void setorderer(int table,QString orderedmenu) //告诉数据库某桌位（table）
     *                                                  的点餐情况(orderedmenu）
     *                                                 【格式：000123020300001】
     * QString getordered(int table) //从数据库获取某桌(table)点餐情况
     *                                【格式：葱爆西瓜#22#鱼香菠萝#30#烤芒果#20】
     * QString getorigmenu(); //从数据库获取原始菜单
     *                         【格式：葱爆西瓜#22#红烧芝麻#12#鱼香菠萝#30#烤芒果#20】
     * void addMenu(QString); //前台设置菜单，加菜 【格式：凉拌米饭*12*爆炒柠檬*13】
     * void deleteMenu(QString); //前台设置菜单，删菜 【格式：红烧芝麻*烤芒果】
     */
    void dealLeave(QMap<QString, QString> message);
    void dealOrder(QMap<QString, QString> message);
    void dealCallServe(QMap<QString, QString> message);

private:
    TableWidget* m_database;

protected:
    //只要出现一个新的连接，就会调用这个函数
    virtual void incomingConnection(int socketDescriptor);

protected slots:
    //用来处理tcpclientsocket发来的信号
    void slotupdateserver(QMap<QString, QString> message);

    //有人断开连接
    void slotclientdisconnect(int);

signals:
    //发送给前台，有新顾客上桌
    void newclientontable(int,int);

    //发送给前台界面，有人点餐
    void ordermenu( int,QString);

    //发送给前台，有人叫服务
    void callserver(int);

    //发送给前台，有人离开
    void clientleave(int);



};

#endif // SERVER_H
