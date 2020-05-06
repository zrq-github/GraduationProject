#include "IMQTcpWord.h"
#include "DataAnalysis.h"
#include "DataCenter.h"
#include <QTcpSocket>

IMQTcpWord & IMQTcpWord::getInstance()
{
    static IMQTcpWord m_imQTcpWord;
    return m_imQTcpWord;
}


QTcpSocket * IMQTcpWord::getSocket()
{
    return m_socket;
}

void IMQTcpWord::connectHost(QString address, quint16 port)
{
    m_socket->connectToHost(address, port);

    connect(m_socket, &QTcpSocket::readyRead, this, &IMQTcpWord::slotSocketReadData);
}

void IMQTcpWord::slotSocketReadData()
{
    QByteArray byte = m_socket->readAll();
    MsgInfo msgInfo = DataAnalysis::msgFromJsonByte(byte);

    if (msgInfo.msgType == MsgType::USERLOGINSUCCEED)
    {
        UserInfo userInfo = DataAnalysis::userFromJsonByte(byte);
        DataCenterInst.setMyInfo(std::make_shared<UserInfo>(userInfo));
        emit signLogonSucceed();
        return;
    }
    switch (msgInfo.msgType)
    {
    case MsgType::USERMSG:
    {
        //MsgInfoPtr msgInfo = std::make_shared<MsgInfo>(msgInfo);
        emit signChatMsg(msgInfo);
    }
    break;
    default:
        break;
    }
}

IMQTcpWord::IMQTcpWord()
{   //初始化socket对象,每个程序带唯一一个socket
    m_socket = new QTcpSocket;
}
