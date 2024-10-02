#include "server.h"

#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>
#include <QVector>

Server::Server()
{
    if (!listen(QHostAddress::Any, 8080))
    {
        qDebug() << "Ошибка прослушивания на порту!";
    }
    m_dbManager = new DataBaseManager();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    m_socket = new QTcpSocket();
    m_socket->setSocketDescriptor(socketDescriptor);
    qDebug() << "New conenction! " << socketDescriptor;
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
            qDebug() << "Get message";
            QString name;
            QString text;
            in >> name;
            in >> text;
            args.push_back(QString(name + ": " + text));
            m_dbManager->addMessage(name, text);
            sendToAll(code, args);
        }
        else if (code == 1)
        {
            QString name;
            QString password;
            in >> name >> password;
            bool isLogin = m_dbManager->tryLogin(name, password);
            args.push_back(isLogin);
            if (isLogin)
            {
                qDebug() << "Login";
                QVector<QString> messages = m_dbManager->get100Message();
                for (const auto& msg : messages)
                {
                    args.push_back(msg);
                }
            }
            else
            {
                args.push_back("");
            }
            sendToClient(code, m_socket, args);
        }
        else if (code == 2)
        {
            QString name;
            QString password;
            in >> name >> password;
            args.push_back(m_dbManager->tryRegistration(name, password));
            sendToClient(code, m_socket, args);
        }
    }
}

void Server::sendToAll(qint8 code, const QVariantList& args)
{
    m_data.clear();
    qDebug() << "send to all ";


    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << code;
    out << args[0].toString();

    for (int i = 0; i < m_sockets.size(); ++i)
    {
        m_sockets[i]->write(m_data);
    }
}

void Server::sendToClient(qint8 code, QTcpSocket* client, const QVariantList& args)
{
    m_data.clear();

    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << code;
    if (code == 0)
    {
        out << args[0].toString();
    }
    else if (code == 1)
    {
        out << args[0].toBool();
        out << args.size();
        qDebug() << args.size();
        for(int i = 1; i < args.size(); ++i)
        {
            out << args[i].toString();
        }

    }
    else if (code == 2)
    {
        out << args[0].toBool();
    }
    client->write(m_data);
}
