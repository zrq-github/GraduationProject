#include "chat.h"
#include "ui_chat.h"

#include <QDialog>
#include <QtNetwork>
#include <QtGui>
#include "tcpclient.h"
#include "tcpserver.h"

#include <QUdpSocket>
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>

#include "tcpserver.h"
#include "tcpclient.h"
#include <QFileDialog>



chat::chat(QString pasvusername, QString pasvuserip, QString Name) : ui(new Ui::chat)
{
    name = Name;
    ui->setupUi(this);
    ui->textEdit->setFocusPolicy(Qt::StrongFocus);
    ui->textBrowser->setFocusPolicy(Qt::NoFocus);

    ui->textEdit->setFocus();
    ui->textEdit->installEventFilter(this);

    a = 0;
    is_opened = false;

    xpasvusername = pasvusername;
    xpasvuserip = pasvuserip;

    ui->label->setText(tr("与%1聊天中.").arg(xpasvusername));

    //UDP部分
    xchat = new QUdpSocket(this);
    xport = 45456;
    xchat->bind(xport, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    //xchat->bind( QHostAddress::QHostAddress(getIP()), xport );
    connect(xchat, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));

}


chat::~chat()
{
    is_opened = false;
    delete ui;
}



//处理用户离开
void chat::participantLeft(QString userName, QString time)
{
    ui->textBrowser->setTextColor(Qt::gray);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->textBrowser->append(tr("%1 于 %2 离开！.").arg(userName).arg(time));
}

QString chat::getUserName()  //获取用户名
{

    return name;

}

QString chat::getIP()  //获取ip地址
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, list)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol) //我们使用IPv4地址
            return address.toString();
    }
    return 0;
}



QString chat::getMessage()  //获得要发送的信息
{
    QString msg = ui->textEdit->toHtml();
    qDebug() << msg;
    ui->textEdit->clear();
    ui->textEdit->setFocus();
    return msg;
}




//通过私聊套接字发送到对方的私聊专用端口上
void chat::sendMessage(MessageType type, QString serverAddress)  //发送信息
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    //QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    out << type << getUserName();


    switch (type)
    {
    case ParticipantLeft:
    {
        break;
    }
    case Message:
    {

        message = getMessage();
        out << address << message;
        ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());
        break;
    }
    case FileName:
    {
        QString clientAddress = xpasvuserip;
        out << address << clientAddress << FileName;
        break;
    }
    case Refuse:
    {
        out << serverAddress;
        break;
    }
    }
    xchat->writeDatagram(data, data.length(), QHostAddress(xpasvuserip), 45456);

}






void chat::on_send_clicked()
{
    sendMessage(Message);
    //QString localHostName = QHostInfo::localHostName();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    ui->textBrowser->setTextColor(Qt::gray);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman", 12));
    ui->textBrowser->append("[ " + xpasvusername + " ] " + time);
    ui->textBrowser->append(message);
    //    is_opened = true;

}



void chat::processPendingDatagrams()   //接收数据UDP
{
    while (xchat->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(xchat->pendingDatagramSize());
        xchat->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName, ipAddress, messagestr;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch (messageType)
        {
        case Xchat:
        {

            break;
        }
        case Message:
        {
            //这2条语句都没有用。why？？、
            /*this->hide();
            this->close();*/
            in >> userName >> ipAddress >> messagestr;
            ui->textBrowser->setTextColor(Qt::blue);
            ui->textBrowser->setCurrentFont(QFont("Times New Roman", 12));
            ui->textBrowser->append("[ " + userName + " ] " + time);//与主机名聊天中
            ui->textBrowser->append(messagestr);
            //        ui->textBrowser->show();
                    //this->textBrowser->setTextColor(Qt::blue);
                    //this->textBrowser->setCurrentFont(QFont("Times New Roman",12));
                    //this->textBrowser->append("[ " +localHostName+" ] "+ time);//与主机名聊天中
                    //this->textBrowser->append(messagestr);

            //        a ++;
            //        if( is_opened == false )//加了这句，接收端B不显示端口了
            {
                this->show();//解决bug1.收到私聊消息后才显示
        //        ui->textBrowser->show();
            //    this->show();
        //        ui->textBrowser->show();
            //    ui.show();
            //    if( this->show() )
        //        this->hide();
        //        0 == a;
                is_opened = true;
            }
            break;
        }
        //        case FileName:
        //            {
        //                in >>userName >>localHostName >> ipAddress;
        //                QString clientAddress,fileName;
        //                in >> clientAddress >> fileName;
        //                //hasPendingFile(userName,ipAddress,clientAddress,fileName);
        //                break;
        //            }
        //        case Refuse:
        //            {
        //                in >> userName ;
        //                QString serverAddress;
        //                in >> serverAddress;
        //                QString ipAddress = getIP();

        //                if(ipAddress == serverAddress)
        //                {
        //                    server->refused();
        //                }
        //                break;
        //            }
        case ParticipantLeft:
        {
            in >> userName;
            participantLeft(userName, time);
            QMessageBox::information(0, tr("本次对话关闭."), tr("对方结束了对话."), QMessageBox::Ok);
            a = 1;
            ui->textBrowser->clear();
            //is_opened = true;
        //    this->is_opened = false;
            ui->~chat();
            close();
            //    delete ui;
            //    ui = 0;
            break;
        }
        }
    }
}
