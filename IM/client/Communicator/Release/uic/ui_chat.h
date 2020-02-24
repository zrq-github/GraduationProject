/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_chat
{
public:
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QPushButton *send;
    QLabel *label;

    void setupUi(QDialog *chat)
    {
        if (chat->objectName().isEmpty())
            chat->setObjectName(QStringLiteral("chat"));
        chat->resize(608, 479);
        textBrowser = new QTextBrowser(chat);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(60, 30, 481, 301));
        textEdit = new QTextEdit(chat);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(60, 340, 481, 79));
        send = new QPushButton(chat);
        send->setObjectName(QStringLiteral("send"));
        send->setGeometry(QRect(440, 420, 113, 32));
        label = new QLabel(chat);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 371, 16));

        retranslateUi(chat);

        QMetaObject::connectSlotsByName(chat);
    } // setupUi

    void retranslateUi(QDialog *chat)
    {
        chat->setWindowTitle(QApplication::translate("chat", "Dialog", Q_NULLPTR));
        send->setText(QApplication::translate("chat", "send", Q_NULLPTR));
        label->setText(QApplication::translate("chat", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class chat: public Ui_chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
