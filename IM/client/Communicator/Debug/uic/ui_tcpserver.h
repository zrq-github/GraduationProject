/********************************************************************************
** Form generated from reading UI file 'tcpserver.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVER_H
#define UI_TCPSERVER_H

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

class Ui_TcpServer
{
public:
    QPushButton *serverCloseBtn;
    QPushButton *serverOpenBtn;
    QLabel *serverStatusLabel;
    QPushButton *serverSendBtn;
    QProgressBar *progressBar;

    void setupUi(QDialog *TcpServer)
    {
        if (TcpServer->objectName().isEmpty())
            TcpServer->setObjectName(QStringLiteral("TcpServer"));
        TcpServer->resize(330, 242);
        serverCloseBtn = new QPushButton(TcpServer);
        serverCloseBtn->setObjectName(QStringLiteral("serverCloseBtn"));
        serverCloseBtn->setGeometry(QRect(210, 120, 75, 32));
        serverOpenBtn = new QPushButton(TcpServer);
        serverOpenBtn->setObjectName(QStringLiteral("serverOpenBtn"));
        serverOpenBtn->setGeometry(QRect(20, 120, 73, 32));
        serverStatusLabel = new QLabel(TcpServer);
        serverStatusLabel->setObjectName(QStringLiteral("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(20, 50, 281, 16));
        serverSendBtn = new QPushButton(TcpServer);
        serverSendBtn->setObjectName(QStringLiteral("serverSendBtn"));
        serverSendBtn->setGeometry(QRect(120, 120, 72, 32));
        progressBar = new QProgressBar(TcpServer);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(100, 90, 95, 20));
        progressBar->setValue(0);

        retranslateUi(TcpServer);

        QMetaObject::connectSlotsByName(TcpServer);
    } // setupUi

    void retranslateUi(QDialog *TcpServer)
    {
        TcpServer->setWindowTitle(QApplication::translate("TcpServer", "File", Q_NULLPTR));
        serverCloseBtn->setText(QApplication::translate("TcpServer", "close", Q_NULLPTR));
        serverOpenBtn->setText(QApplication::translate("TcpServer", "open", Q_NULLPTR));
        serverStatusLabel->setText(QApplication::translate("TcpServer", "Please choose file.", Q_NULLPTR));
        serverSendBtn->setText(QApplication::translate("TcpServer", "send", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TcpServer: public Ui_TcpServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVER_H
