#include "server.h"

#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>

Server::Server()
{
    listen(QHostAddress::LocalHost, 2222);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(socketDescriptor);

    connect(m_socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    m_sockets.push_back(m_socket);
}
void Server::slotReadyRead()
{
    m_socket = (QTcpSocket*)sender();
    QDataStream in(m_socket);
    if (in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        if (str == "")
        {
            qDebug() << "Data error!";
            return;
        }
        sendToClient(str);
        qDebug() << str + " sended";
    }
}

void Server::sendToClient(QString str)
{
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << str;
    for (int i = 0; i < m_sockets.size(); ++i)
    {
        m_sockets[i]->write(m_data);
    }
}
