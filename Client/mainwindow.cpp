#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "loginform.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("QLabel {background-color : white;}");
    ui->label->setAlignment(Qt::AlignTop);

    setFixedSize(500,800);
}

void MainWindow::addMessage(QString str)
{
    ui->label->setText(ui->label->text() + str + "\n");
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

MainWindow::~MainWindow()
{
    delete ui;
}
