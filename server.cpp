#include "server.h"
#include <QHostAddress>
#include "QMessageBox"
#include "aaaaaaa/tablewidget.h"
#include <QDebug>

Server::Server(QObject *parent, int port):QTcpServer(parent)
{
    //开始监听
    listen(QHostAddress::Any, port);
    m_database = new TableWidget;
}

//- Function Name: incomingConnection
//– Description: 当监听到新的连接时，调用该函数
//– Created: 18/08/30
//– Parameter: socketDescriptor, int, input
//– Return Code: VOID
//– Author: 张潇艺
void Server::incomingConnection(int socketDescriptor)
{
    qDebug()<<"newconnection";
    //只要有新的连接就生成一个新的通信套接字
    TcpClientSocket *tcpclientsocket = new TcpClientSocket(this);

    //将新创建的信号套接字描述符指定为参数socketdescriptor
    tcpclientsocket->setSocketDescriptor(socketDescriptor);

    //将这个套接字加入客户端套接字列表中
    tcpclientsocketlist.append(tcpclientsocket);

    //接收到tcpclientsocket发送来的更新界面的信号
    connect(tcpclientsocket, &TcpClientSocket::updateserver, this, &Server::slotupdateserver);
    connect(tcpclientsocket, &TcpClientSocket::clientdisconnected, this, &Server::slotclientdisconnect);

    //使数据库更新信息，并得到编号
    int num = m_database->addRow();

    //获取桌号
    int table = m_database->getTable(num);
    qDebug()<<table;


    //如果能直接上桌
    if(table != 0)
    {
        //发送给顾客
        QMap<QString, QString> message;
        message["MessageKind"] = "OnTable";
        message["Table"] = QString::number(table);
        message["Num"] = QString::number(num);
        message["MenuList"] = m_database->getList();;
        tcpclientsocket->sendMessage(message);

        //发送给前台
        emit newclientontable(num,table);
    }

    //如果不能上桌
    else if(table==0)
    {
        //从数据库获取前方排队人数
        int front = m_database->getFront(num);

        //发送给客户相关信息
        QMap<QString, QString> message;
        message["MessageKind"] = "GoQueue";
        message["Num"] = QString::number(num);
        message["Front"] = QString::number(front);
        message["MenuList"] = m_database->getList();
        tcpclientsocket->sendMessage(message);
    }

}

//- Function Name: slotupdateserver
//– Description: 客户端发送消息过来，根据此函数判断消息类型
//-              协议：Leave---该客户离开餐厅
//-                   Order---该客户点餐
//-                   CallServer---该客户叫服务
//– Created: 18/08/28
//– Parameter: message, QMap, input
//– Return Code: VOID
//– Author: 张潇艺
void Server::slotupdateserver(QMap<QString, QString> message)
{
    QString kind = message["MessageKind"];
    if(kind == "Leave")
    {
        dealLeave(message);
    }
    else if(kind == "Order")
    {
        dealOrder(message);
    }
    else if(kind == "CallServe")
    {
        dealCallServe(message);
    }
    else
        qDebug()<<"wrong message";


}

//- Function Name: slotclientdisconnected
//– Description: 有顾客断线
//– Created: 18/08/28
//– Parameter: descriptor, int, input
//– Return Code: VOID
//– Author: 张潇艺
void Server::slotclientdisconnect(int descriptor)
{
    //删除列表中离开的顾客
    for(int i = 0; i < tcpclientsocketlist.count(); i++)
    {
        TcpClientSocket *item = tcpclientsocketlist.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            tcpclientsocketlist.removeAt(i);
            return;
        }
    }
    return;
}

//- Function Name: dealLeave
//– Description: 有顾客离开餐厅
//– Created: 18/08/31
//– Parameter: message, QMap, input
//– Return Code: VOID
//– Author: 张潇艺
void Server::dealLeave(QMap<QString, QString> message)
{
    //获取离开桌位
    int table = message["Table"].toInt();

    //告诉数据库
    int nextnum = m_database->acceptPay(table);

    //告诉前台
    emit clientleave(table);

    //如果后面有顾客
    if(nextnum)
    {
        //获取新上桌顾客的编号和桌位
        int newtable = m_database->getTable(nextnum);

        //发送给前台
        emit newclientontable(newtable,nextnum);

        //发送给各个客户
        QString client=QString::number(nextnum);
        QString table= QString::number(newtable);
        for(int i = 0; i < tcpclientsocketlist.count();i++)
        {
            TcpClientSocket *item = tcpclientsocketlist.at(i);
            QMap<QString, QString> message;
            message["MessageKind"] = "NextClient";
            message["Num"] = client;
            message["Table"] = table;
            item->sendMessage(message);
        }
    }
}

//- Function Name: dealOrder
//– Description: 有顾客点餐
//– Created: 18/08/31
//– Parameter: message, QMap, input
//– Return Code: VOID
//– Author: 张潇艺
void Server::dealOrder(QMap<QString, QString> message)
{
    //获取桌号
    int table = message["Table"].toInt();

    //获取点餐内容
    QString ordered = message["Ordered"];

    //向数据库发送相关信息,并获取点餐内容text    
    m_database->acceptFood(table, ordered);
    QString orderedmenu = m_database->getOrdered(table);
    qDebug()<<orderedmenu;

    //发送给前台
    emit ordermenu(table, orderedmenu);
}

//- Function Name: dealCallServe
//– Description: 有顾客叫服务
//– Created: 18/08/31
//– Parameter: message, QMap, input
//– Return Code: VOID
//– Author: 张潇艺
void Server::dealCallServe(QMap<QString, QString> message)
{
    //获取桌号
    int table = message["Table"].toInt();

    //发送给前台
    emit callserver(table);
}

