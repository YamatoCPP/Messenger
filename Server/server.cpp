#include "server.h"

#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>

Server::Server()
{
    listen(QHostAddress::LocalHost, 2222);
    m_dbManager = new DataBaseManager();
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
    qDebug() << "Get message";

    m_socket = (QTcpSocket*)sender();
    QDataStream in(m_socket);
    if (in.status() == QDataStream::Ok)
    {
        qint8 code;
        in >> code;
        QVariantList args;
        if (code == 0)
        {
            QString str;
            in >> str;
            args.push_back(str);
        }
        if (code == 1)
        {
            QString name;
            QString password;
            in >> name >> password;
            args.push_back(m_dbManager->tryLogin(name, password));
        }
        sendToClient(code, args);
    }
}

void Server::sendToClient(qint8 code, const QVariantList& args)
{
    m_data.clear();
    qDebug() << code << args;

    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << code;
    if (code == 0)
        out << args[0].toString();
    else
        out << args[0].toBool();
    for (int i = 0; i < m_sockets.size(); ++i)
    {
        m_sockets[i]->write(m_data);
    }
}
