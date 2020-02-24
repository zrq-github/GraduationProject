/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextBrowser *messageBrowser;
    QTextEdit *messageTextEdit;
    QTableWidget *userTableWidget;
    QPushButton *sendToolButton;
    QPushButton *save;
    QPushButton *boldToolBtn;
    QPushButton *sendButton;
    QPushButton *pinkButtun;
    QPushButton *gray;
    QPushButton *lightblue;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(835, 502);
        Widget->setAutoFillBackground(true);
        messageBrowser = new QTextBrowser(Widget);
        messageBrowser->setObjectName(QStringLiteral("messageBrowser"));
        messageBrowser->setGeometry(QRect(10, 10, 401, 341));
        messageTextEdit = new QTextEdit(Widget);
        messageTextEdit->setObjectName(QStringLiteral("messageTextEdit"));
        messageTextEdit->setGeometry(QRect(10, 380, 401, 71));
        userTableWidget = new QTableWidget(Widget);
        if (userTableWidget->columnCount() < 2)
            userTableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        userTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        userTableWidget->setObjectName(QStringLiteral("userTableWidget"));
        userTableWidget->setGeometry(QRect(420, 10, 391, 441));
        sendToolButton = new QPushButton(Widget);
        sendToolButton->setObjectName(QStringLiteral("sendToolButton"));
        sendToolButton->setGeometry(QRect(50, 350, 31, 31));
        QIcon icon;
        icon.addFile(QStringLiteral(":/myimage/imgs/imgs/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        sendToolButton->setIcon(icon);
        sendToolButton->setIconSize(QSize(22, 22));
        sendToolButton->setFlat(true);
        save = new QPushButton(Widget);
        save->setObjectName(QStringLiteral("save"));
        save->setGeometry(QRect(380, 350, 31, 31));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/imgs/imgs/QtChat.ico"), QSize(), QIcon::Normal, QIcon::Off);
        save->setIcon(icon1);
        save->setIconSize(QSize(22, 22));
        save->setFlat(true);
        boldToolBtn = new QPushButton(Widget);
        boldToolBtn->setObjectName(QStringLiteral("boldToolBtn"));
        boldToolBtn->setGeometry(QRect(10, 350, 31, 31));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/imgs/imgs/bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        boldToolBtn->setIcon(icon2);
        boldToolBtn->setIconSize(QSize(22, 22));
        boldToolBtn->setFlat(true);
        sendButton = new QPushButton(Widget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setGeometry(QRect(330, 460, 81, 32));
        pinkButtun = new QPushButton(Widget);
        pinkButtun->setObjectName(QStringLiteral("pinkButtun"));
        pinkButtun->setGeometry(QRect(90, 350, 51, 31));
        pinkButtun->setStyleSheet(QStringLiteral(" QPushButton:hover { background-color: rgba(255, 198, 199, 217); }"));
        gray = new QPushButton(Widget);
        gray->setObjectName(QStringLiteral("gray"));
        gray->setGeometry(QRect(150, 350, 51, 31));
        gray->setStyleSheet(QStringLiteral(" QPushButton:hover { background-color: rgb(161, 161, 161); }"));
        lightblue = new QPushButton(Widget);
        lightblue->setObjectName(QStringLiteral("lightblue"));
        lightblue->setGeometry(QRect(210, 350, 51, 31));
        lightblue->setStyleSheet(QStringLiteral(" QPushButton:hover{ background-color:rgba(160, 175, 230, 235); }"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Grouptalk", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = userTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "username", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = userTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Widget", "IP", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        sendToolButton->setToolTip(QApplication::translate("Widget", "File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        sendToolButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        save->setToolTip(QApplication::translate("Widget", "Save", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        save->setText(QString());
#ifndef QT_NO_TOOLTIP
        boldToolBtn->setToolTip(QApplication::translate("Widget", "Bold", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        boldToolBtn->setText(QString());
        sendButton->setText(QApplication::translate("Widget", "send", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        sendButton->setShortcut(QApplication::translate("Widget", "Meta+Return", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        pinkButtun->setText(QApplication::translate("Widget", "pink", Q_NULLPTR));
        gray->setText(QApplication::translate("Widget", "gray", Q_NULLPTR));
        lightblue->setText(QApplication::translate("Widget", "blue", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
