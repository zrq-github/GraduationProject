#ifndef IMQTcpSocket_H_
#define IMQTcpSocket_H_

#include "datacenter_global.h"
#include "BaseDataType.h"
#include <QTcpSocket>

#define IMQTcpWordInstance IMQTcpWord::getInstance()
#define IMQTcpSocket IMQTcpWord::getInstance().getSocket()


class DATACENTER_EXPORT IMQTcpWord :public QObject
{
    Q_OBJECT
public:
    IMQTcpWord();
    static IMQTcpWord &getInstance();
    QTcpSocket *getSocket();
    void connectHost(QString address, quint16 port);

signals:
    void signLogonSucceed();
    void signChatMsg(MsgInfo);
    void signFileName(MsgInfo);
    void signVideoChat(MsgInfo);
protected slots:
    void slotSocketReadData();                      //处理服务器返回的信息
private:

    QTcpSocket *m_socket;
};
#endif