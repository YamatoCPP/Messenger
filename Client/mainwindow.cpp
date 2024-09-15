#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("QLabel {background-color : white;}");
    ui->label->setAlignment(Qt::AlignTop);

    setFixedSize(500,800);
    m_socket = new QTcpSocket(this);
    m_socket->connectToHost(QHostAddress::Any, 2222);
    connect(m_socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
}

void MainWindow::slotReadyRead()
{
    QDataStream in(m_socket);
    if (in.status() == QDataStream::Ok)
    {
        QString str;
        in >> str;
        ui->label->setText(ui->label->text() + str + "\n");
    }
}

void MainWindow::sendToServer(QString str)
{
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out << str;
    m_socket->write(m_data);
    ui->lineEdit->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == "") return;
    sendToServer(ui->lineEdit->text());
}


void MainWindow::on_lineEdit_returnPressed()
{
    if (ui->lineEdit->text() == "") return;
    sendToServer(ui->lineEdit->text());
}

