#include "widget.h"
#include "ui_widget.h"
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


Widget::Widget(QWidget* parent, QString s) :
    QWidget(parent),
    ui(new Ui::Widget), qstring(s)
{

    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);

    privatechat = 0;
    privatechat1 = 0;
    i = 0;
    bb = 0;
    port = 45454;

    udpSocket->bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    sendMessage(NewParticipant);



    server = new TcpServer(this);
    connect(server, SIGNAL(sendFileName(QString)), this, SLOT(getFileName(QString)));

    ui->messageTextEdit->installEventFilter(this); // +
}

Widget::~Widget()
{
    delete ui;
}







// she zai zhe li xie le yi ge Ctrl+Enter 发送信息
// 使用UDP广播发送信息
void Widget::sendMessage(MessageType type, QString serverAddress)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    //QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    out << type << getUserName();

    switch (type)
    {
    case Message:
        if (ui->messageTextEdit->toPlainText() == "") {
            return;
        }
        out << address << getMessage();
        ui->messageBrowser->verticalScrollBar()
            ->setValue(ui->messageBrowser->verticalScrollBar()->maximum());
        break;

    case NewParticipant:
        out << address;
        break;

    case ParticipantLeft:
        //out<<address;
        break;

    case FileName: {
        int row = ui->userTableWidget->currentRow();
        QString clientAddress = ui->userTableWidget->item(row, 1)->text(); //2 to 1
        out << address << clientAddress << fileName;
        break;
    }

    case Refuse:
        out << serverAddress;
        break;
    }
    udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}

// 接收UDP信息
void Widget::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int messageType;
        in >> messageType;
        QString userName, ipAddress, message;
        QString time = QDateTime::currentDateTime()
            .toString("yyyy-MM-dd hh:mm:ss");

        switch (messageType)
        {
        case Message:
            in >> userName >> ipAddress >> message;
            ui->messageBrowser->setTextColor(Qt::black);
            ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 8));
            ui->messageBrowser->append("[ " + userName + " ] " + time);
            ui->messageBrowser->append(message);
            break;

        case NewParticipant:
            in >> userName >> ipAddress;
            newParticipant(userName, ipAddress);

            break;

        case ParticipantLeft:
            in >> userName;
            participantLeft(userName, time);
            break;

        case FileName:
        {
            in >> userName >> ipAddress;
            QString clientAddress, fileName;
            in >> clientAddress >> fileName;
            //the first para she use localhostname
            hasPendingFile(userName, ipAddress, clientAddress, fileName);
            break;
        }

        case Refuse:
        {
            in >> userName;
            QString serverAddress;
            in >> serverAddress;
            QString ipAddress = getIP();

            if (ipAddress == serverAddress)
            {
                server->refused();
            }
            break;
        }

        case Xchat:
        {
            in >> userName >> ipAddress;
            showxchat(userName, ipAddress, getUserName());//显示与主机名聊天中，不是用户名
            break;
        }
        }
    }
}

// 处理新用户加入
void Widget::newParticipant(QString userName, QString ipAddress)
{
    bool isEmpty = ui->userTableWidget->findItems(userName, Qt::MatchExactly).isEmpty();//IP->USER


    if (isEmpty)
    {
        QTableWidgetItem* user = new QTableWidgetItem(userName);
        //QTableWidgetItem *host = new QTableWidgetItem(localHostName);
        QTableWidgetItem* ip = new QTableWidgetItem(ipAddress);

        ui->userTableWidget->insertRow(0);
        ui->userTableWidget->setItem(0, 0, user);
        //ui->userTableWidget->setItem(0,1,host);
        ui->userTableWidget->setItem(0, 1, ip);
        ui->messageBrowser->setTextColor(Qt::gray);
        ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 10));
        ui->messageBrowser->append(tr("%1 online.").arg(userName));
        //ui->userNumLabel->setText(tr("onine:%1").arg(ui->userTableWidget->rowCount()));

        sendMessage(NewParticipant);
    }
}


// 处理用户离开
void Widget::participantLeft(QString userName, QString time)
{
    int rowNum = ui->userTableWidget->findItems(userName, Qt::MatchExactly).first()->row();
    ui->userTableWidget->removeRow(rowNum);
    ui->messageBrowser->setTextColor(Qt::gray);
    ui->messageBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->messageBrowser->append(tr("%1 于 %2 left！.").arg(userName).arg(time));
    //ui->userNumLabel->setText(tr("ONLINE：%1").arg(ui->userTableWidget->rowCount()));
}

// 获取ip地址
QString Widget::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress address, list)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return 0;
}

// 获取用户名
QString Widget::getUserName()
{


    return qstring;
}


// 获得要发送的消息
QString Widget::getMessage()
{
    QString msg = ui->messageTextEdit->toHtml();

    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();
    return msg;
}


//发送消息
void Widget::on_sendButton_clicked()
{
    sendMessage(Message);
}



// 获取要发送的文件名
void Widget::getFileName(QString name)
{
    fileName = name;
    sendMessage(FileName);
}

void Widget::on_sendToolButton_clicked()
{
    if (ui->userTableWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, tr("选择用户"),
            tr("请先从用户列表选择要传送的用户！."), QMessageBox::Ok);
        return;
    }


    server->show();
    server->initServer();



}
// 是否接收文件
void Widget::hasPendingFile(QString userName, QString serverAddress,
    QString clientAddress, QString fileName)
{
    QString ipAddress = getIP();
    if (ipAddress == clientAddress)
    {
        int btn = QMessageBox::information(this, tr("接受文件"),
            tr("来自%1(%2)的文件：%3,是否接收？.")
            .arg(userName).arg(serverAddress).arg(fileName),
            QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::Yes)
        {
            QString name = QFileDialog::getSaveFileName(0, tr("保存文件"), fileName);
            if (!name.isEmpty())
            {
                TcpClient* client = new TcpClient(this);
                client->setFileName(name);
                client->setHostAddress(QHostAddress(serverAddress));
                client->show();
            }
        }
        else

            sendMessage(Refuse, serverAddress);

    }
}


void Widget::on_save_clicked()//保存聊天记录
{
    if (ui->messageBrowser->document()->isEmpty())
        QMessageBox::warning(0, tr("警告"), tr("聊天记录为空，无法保存！"), QMessageBox::Ok);
    else
    {
        //获得文件名,注意getSaveFileName函数的格式即可
        QString fileName = QFileDialog::getSaveFileName(this, tr("保存聊天记录"), tr("聊天记录"), tr("文本(*.txt);;All File(*.*)"));
        if (!fileName.isEmpty())
            saveFile(fileName);
    }
}



void Widget::on_userTableWidget_doubleClicked(QModelIndex index)
{

    if (!privatechat) {
        //  chat *privatechatTemp;
        privatechat = new chat(ui->userTableWidget->item(index.row(), 0)->text(), //接收主机名
            ui->userTableWidget->item(index.row(), 1)->text(), qstring);//接收用户IP
    }
    //        if( privatechat->is_opened )delete privatechat;//如果其曾经显示过则删除掉
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    //QString localHostName = QHostInfo::localHostName();
    QString address = getIP();
    out << Xchat << getUserName() << address;
    udpSocket->writeDatagram(data, data.length(), QHostAddress(ui->userTableWidget->item(index.row(), 1)->text()), port);

    //        privatechat->xchat->writeDatagram(data,data.length(),QHostAddress::QHostAddress(ui->tableWidget->item(index.row(),2)->text()), 45456);
          //  if(!privatechat->is_opened)
    privatechat->show();
    privatechat->is_opened = true;
    //    (privatechat->a) = 0;
  //  }

}




void Widget::showxchat(QString name, QString ip, QString myname)
{
    //    if(!privatechat){
     // chat *privatechatTemp;
    if (!privatechat1)
        privatechat1 = new chat(name, ip, myname);
    privatechat1->show();


}


bool Widget::saveFile(const QString& fileName)//保存文件
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("保存文件"),
            tr("无法保存文件 %1:\n %2").arg(fileName)
            .arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->messageBrowser->toPlainText();

    return true;
}



void Widget::on_boldToolBtn_clicked()
{
    i++;
    if (i & 1)
    {
        ui->messageTextEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->messageTextEdit->setFontWeight(QFont::Normal);
    }
    ui->messageTextEdit->setFocus();

}

void Widget::on_pinkButtun_clicked()
{
    this->setAutoFillBackground(true);;
    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor("light pink"));
    this->setPalette(p);

}

void Widget::on_gray_clicked()
{
    this->setAutoFillBackground(true);;
    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor("silver"));
    this->setPalette(p);
}






void Widget::on_lightblue_clicked()
{
    this->setAutoFillBackground(true);;
    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor("light blue"));
    this->setPalette(p);
}


