#include "IMQTcpWord.h"

IMQTcpWord *IMQTcpWord::m_imQTcpWord = nullptr;

IMQTcpWord & IMQTcpWord::getInstance()
{
    if (m_imQTcpWord == nullptr)
    {
        m_imQTcpWord = new IMQTcpWord;
    }
    return *m_imQTcpWord;
}


QTcpSocket * IMQTcpWord::getSocket()
{
    return m_socket;
}

IMQTcpWord::IMQTcpWord()
{
    m_socket = new QTcpSocket;
}
