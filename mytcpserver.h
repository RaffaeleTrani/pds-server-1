#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QList>


class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    
signals:

public slots:
    void newConnection();
    void DBConnection();
private:
    QTcpServer *server;
    QList<QTcpSocket *>SocketList;
    int counter;
};

#endif // MYTCPSERVER_H
