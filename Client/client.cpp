#include "client.h"
#include "loginform.h"
#include "mainwindow.h"
#include "registration.h"


#include <QIODevice>
#include <QObject>
#include <QHostAddress>
#include <QIcon>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Client::Client(QObject* parent)
    : QObject(parent)
{
    m_windows = new QStackedWidget;
    m_windows->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1); ");
    m_windows->setWindowIcon(QIcon("./../../Images/Icon.ico"));

    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::Any, 8080);

    if (!m_socket->waitForConnected(5000))
    {
        qDebug() << "Not connect\n";
        return;
    }

    MainWindow* mainWindow = new MainWindow();
    LoginForm* loginForm = new LoginForm();
    RegistrationForm* registrationForm = new RegistrationForm();

    m_windows->addWidget(loginForm);
    m_windows->addWidget(registrationForm);
    m_windows->addWidget(mainWindow);

    QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    QObject::connect(mainWindow, &MainWindow::sendToServer, this, &Client::sendToServer);
    QObject::connect(loginForm, &LoginForm::login, this, &Client::login);
    QObject::connect(loginForm, &LoginForm::toRegistrForm, [this](){ m_windows->setCurrentIndex(1); });
    QObject::connect(registrationForm, &RegistrationForm::registration, this, &Client::registration);

    m_windows->setCurrentIndex(0);
    m_windows->show();
}

void Client::slotReadyRead()
{
    qDebug() << "Get data";
    QByteArray data = m_socket->readAll();
    QJsonDocument inData = QJsonDocument::fromJson(data);
    QJsonObject json = inData.object();

    if (!inData.isNull())
    {
        int code = json["code"].toInt();

        switch (code)
        {
        case 0:
        {
            QString msg = json["text"].toString();
            ((MainWindow*)m_windows->widget(2))->addMessage(msg);

            break;
        }
        case 1:
        {
            if (json["isLogin"].toBool())
            {
                QJsonArray msgArray = json["messages"].toArray();

                for (const auto& i : msgArray)
                {
                    QString str = i.toString();
                    if (!str.isEmpty())
                    {
                        ((MainWindow*)m_windows->widget(2))->addMessage(str);
                    }
                }
                m_windows->setCurrentIndex(2);
            }
            else
            {
                qDebug() << "Not login";
            }
        }
        case 2:
        {
            if (json["isRegistration"].toBool())
            {
                m_windows->setCurrentIndex(0);
            }
            else
            {
                ((RegistrationForm*)m_windows->widget(1))->setError("Не удалось зарегаться");
            }
        }
        }
    }
}

void Client::sendToServer(QString str)
{
    m_data.clear();

    QJsonObject json;
    json["code"] = 0;
    json["name"] = m_userName;
    json["text"] = str;

    QJsonDocument outData(json);
    m_data = outData.toJson();
    m_socket->write(m_data);
    m_socket->flush();
}

void Client::login(QString name, QString password)
{
    qDebug() << "try login with " + name + " " + password;
    m_userName = name;

    QJsonObject json;
    json["code"] = 1;
    json["name"] = name;
    json["password"] = password;

    QJsonDocument outData(json);
    m_data = outData.toJson();
    m_socket->write(m_data);
    m_socket->flush();
}

void Client::registration(QString name, QString password)
{
    m_data.clear();

    QJsonObject json;
    json["code"] = 2;
    json["name"] = name;
    json["password"] = password;

    QJsonDocument outData(json);
    m_data = outData.toJson();
    m_socket->write(m_data);
    m_socket->flush();
}
