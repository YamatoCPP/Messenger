#ifndef SERVER_H
#define SERVER_H

#include "databasemanager.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QVector>
#include <QByteArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);
private:
    void sendToClient(const QJsonDocument& args);
    void sendToClient(QTcpSocket* client, const QJsonDocument& args);
    QTcpSocket* m_socket;
    QByteArray m_data;
    QVector<QTcpSocket*> m_sockets;
    DataBaseManager* m_dbManager;
};

#endif // SERVER_H
