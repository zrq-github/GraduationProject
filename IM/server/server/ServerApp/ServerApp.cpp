#include "ServerApp.h"
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QHostInfo>
#include "ui_ServerApp.h"
#include <QJsonDocument>
#include <QJsonObject>

#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

ServerApp::ServerApp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerAppClass)
    , hashClients(new QHash<QString, int>)
{
    tcpServer = new IMQTcpServer;
    ui->setupUi(this);
    bindSlots();
}

void ServerApp::closeEvent(QCloseEvent * event)
{
}

void ServerApp::slotBtnSendClick()
{
    //����һ���ַ������Ի��з�����
    QString  msg = ui->editMsg->text();
    ui->plainTextEdit->appendPlainText("[server to client] " + msg);
    ui->editMsg->clear();
    ui->editMsg->setFocus();

    QByteArray  str = msg.toUtf8();
    str.append('\n');//���һ�����з�
    tcpSocket->write(str);
}

void ServerApp::slotStart()
{
    QString IP = ui->comboIP->currentText();//IP��ַ
    quint16 port = ui->spinPort->value();//�˿�
    QHostAddress addr(IP);
    tcpServer->listen(addr, port);//
    if (tcpServer->isListening())
    {
        ui->plainTextEdit->appendPlainText("**��ʼ����...");
        ui->plainTextEdit->appendPlainText("**��������ַ��"
            + tcpServer->serverAddress().toString());
        ui->plainTextEdit->appendPlainText("**�������˿ڣ�"
            + QString::number(tcpServer->serverPort()));
    }

    ui->LabSocketState->setText("����״̬�����ڼ���");
}

void ServerApp::slotNewConnectFromClient(const int descriptor, const QString & address, const quint16 port)
{//ÿ�����������յ������¿ͻ��˵Ĵ����߼�
    ui->plainTextEdit->appendPlainText("NewClient Connect:");
    ui->plainTextEdit->appendPlainText("descriptor:" + QString::number(descriptor));
    ui->plainTextEdit->appendPlainText("address:" + address);
    ui->plainTextEdit->appendPlainText("port:" + QString::number(port));
}

void ServerApp::slotClientDisConnect(const int descriptor, const QString & address, const quint16 port)
{//�ͻ��˶Ͽ�����
    ui->plainTextEdit->appendPlainText("Client Close Connect:");
    ui->plainTextEdit->appendPlainText("descriptor:" + QString::number(descriptor));
    ui->plainTextEdit->appendPlainText("address:" + address);
    ui->plainTextEdit->appendPlainText("port:" + QString::number(port));
}

void ServerApp::slotReadDataFromClient(const int handle, const QString & ip, const quint16 port, const QByteArray & data)
{
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject object = document.object();

    QString &toWho = object.value("to").toString();
    QString &fromWho = object.value("from").toString();
    QString &type = object.value("type").toString();
    QString &dataWho = object.value("data").toString();

    if (toWho == "server")
    {//���͸��������������Ϣ
        if (type == "logon")
        {   //��¼��֤
            //�������ݿ⣬����ж��Ƿ�ɹ�
            if (true)
            {
                hashClients->insert(fromWho, handle); //��userID��socke����
                QJsonObject json;
                json.insert("to", fromWho);
                json.insert("from", toWho);
                json.insert("type", "logon");
                json.insert("data", true);
                QJsonDocument document = QJsonDocument(json);
                emit sendDataToClient(document.toJson(), handle);
            }
        }
    }
    else
    {   //���������û�����Ϣ
        auto i = hashClients->find(toWho);
        if (i != hashClients->end())
        {
            int clientHandle = i.value();
            ui->plainTextEdit->appendPlainText(fromWho+"��"+toWho+"��������Ϣ");
            emit sendDataToClient(data, clientHandle);
        }
        else
        {
            //�û������ߵĴ����¼�
            qDebug() << "���û�:" + toWho + "������";
            ui->plainTextEdit->appendPlainText("���û�:" + toWho + "������");
        }
    }
}

void ServerApp::bindSlots()
{
    //�����ź�
    connect(ui->btnStart, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(slotBtnSendClick()));

    //����IMQTcpServer�������ź�
    connect(tcpServer, &IMQTcpServer::connectClient, this, &ServerApp::slotNewConnectFromClient);
    connect(tcpServer, &IMQTcpServer::sockDisConnect, this, &ServerApp::slotClientDisConnect);
    connect(tcpServer, &IMQTcpServer::readData, this, &ServerApp::slotReadDataFromClient);
    
    connect(this, &ServerApp::sendDataToClient, tcpServer, &IMQTcpServer::slotSendDataToClient);
}

QString ServerApp::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();//����������
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString   localIP = "";

    QList<QHostAddress> addList = hostInfo.addresses();//

    if (!addList.isEmpty())
        for (int i = 0; i < addList.count(); i++)
        {
            QHostAddress aHost = addList.at(i);
            if (QAbstractSocket::IPv4Protocol == aHost.protocol())
            {
                localIP = aHost.toString();
                break;
            }
        }
    return localIP;
}

void ServerApp::slotBtnStartClick()
{

}
