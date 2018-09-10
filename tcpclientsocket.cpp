#include "tcpclientsocket.h"
#include <QDataStream>
#include <QDebug>

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    m_blockSize = 0;
    //客户端发送数据过来就会触发readyread信号
    connect(this, &TcpClientSocket::readyRead, this, &TcpClientSocket::receivedata);
    connect(this, &TcpClientSocket::disconnected, this, &TcpClientSocket::slotclientdisconnect);

}

//- Function Name: sendMessage
//– Description: 发消息给客户端
//– Created: 18/09/03
//– Parameter: message, QMap, input
//– Return Code: VOID
//– Author: 张潇艺
void TcpClientSocket::sendMessage(QMap<QString, QString> message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    // 预存2字节，消息存储结束后，设置实际大小。
    out << (quint16)0;

    // 把消息按照[消息名称：消息内容]的格式进行存储
    foreach (QString key, message.keys()) {
        QString tempmsg = key + ":" + message[key];
        out << tempmsg;
    }

    // 存储消息的大小到预留的位置
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    // 发送消息
    write(block);
}

//- Function Name: receivedata
//– Description: 接收到客户端发来的消息
//– Created: 18/09/03
//– Parameter: VOID
//– Return Code: VOID
//– Author: 张潇艺
void TcpClientSocket::receivedata()
{
    QDataStream in(this);

    // 取得消息的size
    if (m_blockSize == 0)
    {
       if (bytesAvailable() < (quint16)sizeof(quint16)) {
           return;
       }
       in >> m_blockSize;
    }

    // 取得剩余消息的大小，如果不满足size的大小，则返回，等待下次一次读取
    // 已经接收尚未读取的总字节数
    int initBytes = bytesAvailable();
    if (initBytes < m_blockSize)
    {
        return;
    }

    // 读取信息，并且按照[消息名称：消息内容]的格式，进行解析
    QMap<QString, QString> message;
    int msgSize = 0;
    while (m_blockSize > msgSize)
    {
        QString tempmsg;
        in >> tempmsg;
        int idxsplitor = tempmsg.indexOf(":");
        message[tempmsg.mid(0, idxsplitor)] = \
                tempmsg.mid(idxsplitor+1, tempmsg.length()-idxsplitor-1);

        //目前已经读取的字节数
        msgSize = initBytes - bytesAvailable();
    }
    qDebug()<<message;

    // 读取完毕后，发射处理消息的信号
    emit updateserver(message);

    // 有可能一次发送多个消息，所以初始化blocksize，继续接收。
    m_blockSize = 0;
    if (bytesAvailable() > 0)
    {
        this->receivedata();
    }

}

//- Function Name: slotclientdisconnected
//– Description: 检测到客户端断开连接
//– Created: 18/09/03
//– Parameter: VOID
//– Return Code: VOID
//– Author: 张潇艺
void TcpClientSocket::slotclientdisconnect()
{
    qDebug()<<"dis";

    emit clientdisconnected(this->socketDescriptor());
}
