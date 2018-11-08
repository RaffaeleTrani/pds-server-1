#include "mytcpserver.h"
#include <QtSql>

MyTcpServer::MyTcpServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);
    this->counter = 0;
    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));

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
    this->counter++;

    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    qDebug() << "New connection from another client.";

    this->SocketList.append(socket);

    socket->write("Hello client\r\n");
    if (this->counter == 2) {
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
