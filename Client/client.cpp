
#include "client.h"
#include "loginform.h"
#include "mainwindow.h"
#include "registration.h"

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
    RegistrationForm* registrationForm = new RegistrationForm();
    m_windows = new QStackedWidget();

    m_windows->addWidget(loginForm);
    m_windows->addWidget(registrationForm);
    m_windows->addWidget(mainWindow);

    QObject::connect(mainWindow, &MainWindow::sendToServer, this, &Client::sendToServer);
    QObject::connect(loginForm, &LoginForm::login, this, &Client::login);
    QObject::connect(loginForm, &LoginForm::toRegistrForm, [&](){ m_windows->setCurrentIndex(1); });
    QObject::connect(registrationForm, &RegistrationForm::registration, this, &Client::registration);

    m_windows->setCurrentIndex(0);
    m_windows->show();
}

void Client::login(QString name, QString password)
{
    qDebug() << "try login with " + name + " " + password;

    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    qint8 code = 1;
    out << code << name << password;

    m_userName = name;
    m_socket->write(m_data);
}

void Client::registration(QString name, QString password)
{
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    qint8 code = 2;
    out << code << name << password;

    m_socket->write(m_data);
}

void Client::slotReadyRead()
{
    qDebug() << "Get data";
    QDataStream in(m_socket);
    if (in.status() == QDataStream::Ok)
    {
        qint8 code;
        in >> code;
        if (code == 0)
        {
            QString str;
            in >> str;
            MainWindow* mainWindow = (MainWindow*)m_windows->widget(2);
            mainWindow->addMessage(str);
        }
        else if (code == 1)
        {
            bool isLogin;
            in >> isLogin;
            qDebug() << isLogin;
            if (isLogin)
            {
                m_windows->setCurrentIndex(2);
            }
            else
            {
                qDebug() << "Hui";
            }
        }
        else
        {
            bool isRegist;
            in >> isRegist;
            qDebug() << isRegist;
            if (isRegist)
            {
                m_windows->setCurrentIndex(0);
                ((RegistrationForm*)m_windows->widget(1))->setError("");
            }
            else
            {
                ((RegistrationForm*)m_windows->widget(1))->setError("Не удалось зарегаться");
            }
        }
    }
}

void Client::sendToServer(QString str)
{
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    qint8 code = 0;
    out << code << m_userName + ": " + str;
    m_socket->write(m_data);
}
