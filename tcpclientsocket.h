#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include <QTcpSocket>

class TcpClientSocket:public QTcpSocket
{
    Q_OBJECT
public:
    TcpClientSocket(QObject *parent = 0);

    // 发送信息
    void sendMessage(QMap<QString, QString> message);

signals:
    //用来告诉interface需要更新界面的显示
    void updateserver(QMap<QString, QString> message);

    //告诉server有客户端断开连接
    void clientdisconnected(int);

private:
    // 包信息大小
    quint16 m_blockSize;

protected slots:
    //处理readyread信号读取数据
    void receivedata();

    //客户端断开连接触发disconnect信号，这个槽函数用来处理这个信号
    void slotclientdisconnect();

};

#endif // TCPCLIENTSOCKET_H
