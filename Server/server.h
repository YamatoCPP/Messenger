#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QVector>
#include <QByteArray>
#include <QString>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
public slots:
    void slotReadyRead();
    void incomingConnection(qintptr socketDescriptor);
private:
    void sendToClient(QString str);
    QTcpSocket* m_socket;
    QByteArray m_data;
    QVector<QTcpSocket*> m_sockets;
};

#endif // SERVER_H
