#pragma once

#include <QtNetwork/QTcpSocket>

class IMClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    IMClientSocket(QObject *parent=Q_NULLPTR);
    ~IMClientSocket();

private:
    void bindSigns();
private slots:
    void slotConnected();
};
