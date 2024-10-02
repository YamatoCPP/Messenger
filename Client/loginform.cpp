#include "loginform.h"
#include "ui_loginform.h"

#include <QHBoxLayout>
#include <QPalette>
#include <QColor>

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("background-color : white");
    ui->lineEdit_2->setStyleSheet("background-color : white");
    ui->label->setStyleSheet("background-color : rgba(255,255,255,0);");
    ui->label_2->setStyleSheet("background-color : rgba(255,255,255,0);");
    ui->pushButton->setStyleSheet("background-color : rgba(255,255,255,0);");
    ui->pushButton_2->setStyleSheet("background-color : rgba(255,255,255,0);");
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if (!name.isEmpty() && !password.isEmpty())
    {
        login(name, password);
    }
}

void LoginForm::on_pushButton_2_clicked()
{
    toRegistrForm();
}

