#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QString>
#include <QVector>

class DataBaseManager
{
public:
    DataBaseManager();
    bool tryLogin(QString name, QString password);
    bool tryRegistration(QString name, QString password);
    void addMessage(QString name, QString text);
    QVector<QString> get100Message();
private:
    QSqlDatabase m_users;
    QSqlDatabase m_messages;
};

#endif // DATABASEMANAGER_H
