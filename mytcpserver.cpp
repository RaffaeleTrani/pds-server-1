#include "mytcpserver.h"
#include <QtSql>

#define MAX_CLIENTS 2

MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);
    this->connectedClients = 0;
    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect( this, SIGNAL(readyRead()), this, SLOT(readFromClient()));

    if(!server->listen(QHostAddress::Any, 9999))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "Server started!";
    }

    DBConnection();

}

void MyTcpServer::newConnection()
{
    this->connectedClients++;

    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    qDebug() << "New connection from another client.";

    this->SocketList.append(socket);

    socket->write("Hello client\r\n");
    if (this->connectedClients == MAX_CLIENTS) {
        for (QTcpSocket *s : this->SocketList) {
            s->write("Ok");
        }
    }
/*
    socket->flush();

    socket->waitForBytesWritten(3000);

    socket->close(); */
}

void MyTcpServer::DBConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("databasepds");
    db.setUserName("root");
    db.setPassword("");

    if (db.open())
        qDebug() << "Connection to server extablished.";
    else
        qDebug() << "Impossible to connect to server.";

}

void MyTcpServer::readFromClient(){
    QTcpSocket* conn = qobject_cast<QTcpSocket*>(sender());
    QString data;

    while ( conn->canReadLine() ) {
        data = QString(conn->readLine());
        //store data in db
    }
}
