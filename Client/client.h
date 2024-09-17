#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QStackedWidget>
#include <QString>
#include <QObject>

class Client : public QObject
{
public:
    Client(QObject* parent = nullptr);

public slots:
    void slotReadyRead();
    void sendToServer(QString str);
    void login(QString name, QString password);
    void registration(QString name, QString password);
private:
    QTcpSocket* m_socket;
    QByteArray m_data;
    QStackedWidget* m_windows;
};

#endif // CLIENT_H
