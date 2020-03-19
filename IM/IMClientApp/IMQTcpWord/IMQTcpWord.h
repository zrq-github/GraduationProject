#pragma once

#include "imqtcpword_global.h"
#include <QTcpSocket>

#define IMQTcpWordInstance IMQTcpWord::getInstance()
#define IMQTcpSocket IMQTcpWord::getInstance().getSocket()

class IMQTCPWORD_EXPORT IMQTcpWord
{
public:
    static IMQTcpWord &getInstance();

    QTcpSocket *getSocket();
private:
    IMQTcpWord();
    static IMQTcpWord *m_imQTcpWord;
    QTcpSocket *m_socket;
};
