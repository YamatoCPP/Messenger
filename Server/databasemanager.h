#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QString>

class DataBaseManager
{
public:
    DataBaseManager();
    bool tryLogin(QString name, QString password);
private:
    QSqlDatabase m_users;
    QSqlDatabase m_messages;
};

#endif // DATABASEMANAGER_H
