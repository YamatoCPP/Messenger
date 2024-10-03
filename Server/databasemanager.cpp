#include "databasemanager.h"

#include <QDebug>
#include <QSqlQuery>

DataBaseManager::DataBaseManager()
{
    m_users = QSqlDatabase::addDatabase("QSQLITE", "Usersdb");
    m_users.setDatabaseName("./../../Usersdb");
    m_messages = QSqlDatabase::addDatabase("QSQLITE", "Messagesdb");
    m_messages.setDatabaseName("./../../Messagesdb");
}

bool DataBaseManager::tryLogin(QString name, QString password)
{
    m_users.open();
    QSqlQuery getpass("SELECT Password FROM Users WHERE Name == '" + name + "'",
                      m_users);
    if (getpass.exec())
    {
        getpass.next();
        QString pass = getpass.value(0).toString();
        if (!pass.isEmpty() && pass == password)
        {
            m_users.close();
            return true;
        }
    }
    else
    {
        qDebug() << "Query error!";
    }
    m_users.close();
    return false;
}

bool DataBaseManager::tryRegistration(QString name, QString password)
{
    m_users.open();

    QSqlQuery regist(m_users);
    regist.prepare("INSERT INTO Users (Name, Password) VALUES(:name, :password)");
    regist.bindValue(":name", name);
    regist.bindValue(":password", password);

    bool isRegist = false;
    qDebug() << "Rgist";
    if (regist.exec())
    {
        qDebug() << 's';
        isRegist = true;
    }
    else
    {
        qDebug() << "Query error!";
    }

    m_users.close();
    return isRegist;
}

void DataBaseManager::addMessage(QString name, QString text)
{
    m_messages.open();
    QSqlQuery addMessage(m_messages);
    addMessage.prepare("INSERT INTO Messages(Name, Text) VALUES(:name, :text)");
    addMessage.bindValue(":name", name);
    addMessage.bindValue(":text", text);

    if (!addMessage.exec())
    {
        qDebug() << "dbManager: Add Message error";
    }

    m_messages.close();
}

QJsonArray DataBaseManager::get100Message()
{
    m_messages.open();
    QSqlQuery getMessage(m_messages);
    getMessage.prepare("SELECT Name, Text FROM Messages");

    QJsonArray messages;
    if (getMessage.exec())
    {
        while (getMessage.next()) {
            messages.append(getMessage.value(0).toString()
                            + ":\n"
                            + getMessage.value(1).toString()
                            + "\n");
        }
    }
    else
    {
        qDebug() << "Get message error";

    }

    m_messages.close();
    return messages;
}
