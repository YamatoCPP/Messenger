#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginform.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("background-color : white;");
    ui->pushButton->setStyleSheet("background-color : white;");

    QIcon icon("Images/Icon.png");
    setWindowIcon(icon);
}

void MainWindow::addMessage(QString str)
{
    message* msg = new message(str);
    ui->verticalLayout->addWidget(msg);
    ui->verticalLayout->setAlignment(msg, Qt::AlignLeft | Qt::AlignTop);
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty()) return;
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}


void MainWindow::on_lineEdit_returnPressed()
{
    if (ui->lineEdit->text().isEmpty()) return;
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
