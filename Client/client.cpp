#include "client.h"
#include "loginform.h"
#include "mainwindow.h"
#include "registration.h"


#include <QIODevice>
#include <QObject>
#include <QHostAddress>
#include <QIcon>
#include <QVector>

Client::Client(QObject* parent)
    : QObject(parent)
{
    m_windows = new QStackedWidget;
    m_windows->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1); ");
    m_windows->setWindowIcon(QIcon("./../../Images/Icon.ico"));

    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::Any, 8080);

    if (!m_socket->waitForConnected())
    {
        qDebug() << "Not connect\n";
    }
    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);

    MainWindow* mainWindow = new MainWindow();
    LoginForm* loginForm = new LoginForm();
    RegistrationForm* registrationForm = new RegistrationForm();

    m_windows->addWidget(loginForm);
    m_windows->addWidget(registrationForm);
    m_windows->addWidget(mainWindow);

    QObject::connect(mainWindow, &MainWindow::sendToServer, this, &Client::sendToServer);
    QObject::connect(loginForm, &LoginForm::login, this, &Client::login);
    QObject::connect(loginForm, &LoginForm::toRegistrForm, [this](){ m_windows->setCurrentIndex(1); });
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
            QString msg;
            in >> msg;
            ((MainWindow*)m_windows->widget(2))->addMessage(msg);
        }
        else if (code == 1)
        {
            bool isLogin;
            in >> isLogin;

            if (isLogin)
            {
                int size;
                in >> size;
                qDebug() << size;
                QString str;
                for (int i = 0; i < size; ++i)
                {
                    in >> str;
                    if (!str.isEmpty())
                    {
                        ((MainWindow*)m_windows->widget(2))->addMessage(str);
                    }
                }
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
    out << code << m_userName << str;
    m_socket->write(m_data);
}
