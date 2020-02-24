/********************************************************************************
** Form generated from reading UI file 'tcpclient.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPCLIENT_H
#define UI_TCPCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TcpClient
{
public:
    QLabel *tcpClientStatusLabel;
    QProgressBar *progressBar;
    QPushButton *tcpClientCancelBtn;
    QPushButton *tcpClientCloseBtn;

    void setupUi(QDialog *TcpClient)
    {
        if (TcpClient->objectName().isEmpty())
            TcpClient->setObjectName(QStringLiteral("TcpClient"));
        TcpClient->resize(326, 204);
        tcpClientStatusLabel = new QLabel(TcpClient);
        tcpClientStatusLabel->setObjectName(QStringLiteral("tcpClientStatusLabel"));
        tcpClientStatusLabel->setGeometry(QRect(40, 30, 231, 16));
        progressBar = new QProgressBar(TcpClient);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(140, 70, 118, 23));
        progressBar->setValue(0);
        tcpClientCancelBtn = new QPushButton(TcpClient);
        tcpClientCancelBtn->setObjectName(QStringLiteral("tcpClientCancelBtn"));
        tcpClientCancelBtn->setGeometry(QRect(30, 120, 113, 32));
        tcpClientCloseBtn = new QPushButton(TcpClient);
        tcpClientCloseBtn->setObjectName(QStringLiteral("tcpClientCloseBtn"));
        tcpClientCloseBtn->setGeometry(QRect(170, 120, 113, 32));

        retranslateUi(TcpClient);

        QMetaObject::connectSlotsByName(TcpClient);
    } // setupUi

    void retranslateUi(QDialog *TcpClient)
    {
        TcpClient->setWindowTitle(QApplication::translate("TcpClient", "Receive", Q_NULLPTR));
        tcpClientStatusLabel->setText(QApplication::translate("TcpClient", "Please wait.", Q_NULLPTR));
        tcpClientCancelBtn->setText(QApplication::translate("TcpClient", "cancel", Q_NULLPTR));
        tcpClientCloseBtn->setText(QApplication::translate("TcpClient", "close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TcpClient: public Ui_TcpClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPCLIENT_H
