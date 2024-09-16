#include "client.h"
#include "loginform.h"
#include "mainwindow.h"

#include <QIODevice>
#include <QObject>
#include <QHostAddress>

Client::Client(QObject* parent)
    : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::Any, 2222);
    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);

    MainWindow* mainWindow = new MainWindow();
    LoginForm* loginForm = new LoginForm();
    m_windows = new QStackedWidget();

    m_windows->addWidget(loginForm);
    m_windows->addWidget(mainWindow);
    QObject::connect(mainWindow, &MainWindow::sendToServer, this, &Client::sendToServer);
    m_windows->setCurrentIndex(1);
    m_windows->show();
}

void Client::slotReadyRead()
{
    QDataStream in(m_socket);
    if (in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        MainWindow* mainWindow = (MainWindow*)m_windows->widget(1);
        mainWindow->addMessage(str);
    }
}

void Client::sendToServer(QString str)
{
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << str;
    m_socket->write(m_data);
}
