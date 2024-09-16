#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    setFixedSize(500,500);
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

