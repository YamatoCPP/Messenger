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
    ui->lineEdit->setStyleSheet("background-color : white;");
    ui->pushButton->setStyleSheet("background-color : white;");
    ui->label->setAlignment(Qt::AlignTop);

    QIcon icon("Images/Icon.png");
    setWindowIcon(icon);

    setStyleSheet("background-color : violet;");
}

void MainWindow::addMessage(QString str)
{
    ui->label->setText(ui->label->text() + str + "\n");
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == "") return;
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}


void MainWindow::on_lineEdit_returnPressed()
{
    if (ui->lineEdit->text() == "") return;
    sendToServer(ui->lineEdit->text());
    ui->lineEdit->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
