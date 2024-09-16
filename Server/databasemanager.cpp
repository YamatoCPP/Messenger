#include "databasemanager.h"

#include <QDebug>
#include <QSqlQuery>

DataBaseManager::DataBaseManager()
{
    m_users = QSqlDatabase::addDatabase("QSQLITE", "Usersdb");
    m_users.setDatabaseName("./../../Usersdb");
    m_messages = QSqlDatabase::addDatabase("QSQLITE", "Messagesdb");
    m_messages.setDatabaseName("./../../Messagesdb");
    getPass("12");
}

void DataBaseManager::getPass(QString name)
{
    m_users.open();
    QSqlQuery getpass("SELECT Password FROM Users WHERE Name == '" + name + "'",
                      m_users);
    if (getpass.exec())
    {
        getpass.next();
        qDebug() << "Yes, " + getpass.value(0).toString();
    }
    else
    {
        qDebug() << "No";
    }
    m_users.close();
}

