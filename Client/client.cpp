#include "client.h"
#include "loginform.h"
#include "mainwindow.h"
#include "registration.h"


#include <QIODevice>
#include <QObject>
#include <QHostAddress>
#include <QIcon>

Client::Client(QWidget* parent)
    : QStackedWidget(parent)
{
    setStyleSheet("background-color : violet");
    setWindowIcon(QIcon("./../../Images/Icon.ico"));

    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::Any, 2222);
    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);

    MainWindow* mainWindow = new MainWindow();
    LoginForm* loginForm = new LoginForm();
    RegistrationForm* registrationForm = new RegistrationForm();

    addWidget(loginForm);
    addWidget(registrationForm);
    addWidget(mainWindow);

    QObject::connect(mainWindow, &MainWindow::sendToServer, this, &Client::sendToServer);
    QObject::connect(loginForm, &LoginForm::login, this, &Client::login);
    QObject::connect(loginForm, &LoginForm::toRegistrForm, [&](){ setCurrentIndex(1); });
    QObject::connect(registrationForm, &RegistrationForm::registration, this, &Client::registration);

    setCurrentIndex(0);
    show();
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
            qDebug() << code << str;
            ((MainWindow*)widget(2))->addMessage(str);
        }
        else if (code == 1)
        {
            bool isLogin;
            QString str;
            in >> isLogin;
            in >> str;
            qDebug() << isLogin;

            if (isLogin)
            {
                setCurrentIndex(2);
                ((MainWindow*)widget(2))->addMessage(str);
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
                setCurrentIndex(0);
                ((RegistrationForm*)widget(1))->setError("");
            }
            else
            {
                ((RegistrationForm*)widget(1))->setError("Не удалось зарегаться");
            }
        }
    }
}

void Client::sendToServer(QString str)
{
    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    qint8 code = 0;
    out << code << m_userName << str;
    m_socket->write(m_data);
}
