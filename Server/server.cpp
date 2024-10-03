#include "server.h"

#include <QDataStream>
#include <QHostAddress>
#include <QIODevice>

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
    QByteArray data = m_socket->readAll();

    QJsonDocument inData = QJsonDocument::fromJson(data);
    QJsonObject jsonIn = inData.object();


    if (!inData.isNull())
    {
        int code = jsonIn["code"].toInt();

        QJsonDocument outData;
        QJsonObject jsonOut;
        jsonOut["code"] = code;

        switch (code)
        {
        case 0:
        {
            qDebug() << "Get message";

            QString name{jsonIn["name"].toString()};
            QString text{jsonIn["text"].toString()};
            jsonOut["name"] = name;
            jsonOut["text"] = text;

            m_dbManager->addMessage(name, text);

            outData = QJsonDocument(jsonOut);
            sendToClient(outData);

            break;
        }
        case 1:
        {
            QString nameLogin {jsonIn["name"].toString()};
            QString passwordLogin {jsonIn["password"].toString()};

            bool isLogin = m_dbManager->tryLogin(nameLogin, passwordLogin);

            jsonOut["isLogin"] = isLogin;
            if (isLogin)
            {
                qDebug() << "Login";
                jsonOut["messages"] = m_dbManager->get100Message();
            }

            outData = QJsonDocument(jsonOut);
            sendToClient(m_socket, outData);

            break;
        }
        case 2:
        {
            QString nameRegistration {jsonIn["name"].toString()};
            QString passwordRegistration {jsonIn["password"].toString()};

            jsonOut["isRegistration"] = m_dbManager->tryRegistration(nameRegistration, passwordRegistration);

            outData = QJsonDocument(jsonOut);
            sendToClient(outData);

            break;
        }
        }
    }
}

void Server::sendToClient(const QJsonDocument& args)
{
    m_data.clear();

    m_data = args.toJson();
    for (int i = 0; i < m_sockets.size(); ++i)
    {
        m_sockets[i]->write(m_data);
        m_sockets[i]->flush();
    }
}

void Server::sendToClient(QTcpSocket* client, const QJsonDocument& args)
{
    m_data.clear();
    m_data = args.toJson();
    client->write(m_data);
    client->flush();
}
