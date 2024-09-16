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

