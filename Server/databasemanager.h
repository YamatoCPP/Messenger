#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QString>

class DataBaseManager
{
public:
    DataBaseManager();
    bool tryLogin(QString name, QString password);
    bool tryRegistration(QString name, QString password);
    void addMessage(QString name, QString text);
    QString get100Message();
private:
    QSqlDatabase m_users;
    QSqlDatabase m_messages;
};

#endif // DATABASEMANAGER_H
