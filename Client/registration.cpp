#include "registration.h"
#include "ui_registration.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
    ui->nameline->setStyleSheet("background-color : white; ");
    ui->passwordline->setStyleSheet("background-color : white; ");
    ui->passwordline2->setStyleSheet("background-color : white; ");
    ui->errorlbl->setStyleSheet("background-color: rgba(255,255,255,0);");
    ui->namelbl->setStyleSheet("background-color: rgba(255,255,255,0);");
    ui->passwordlbl->setStyleSheet("background-color: rgba(255,255,255,0);");
    ui->passwordlbl2->setStyleSheet("background-color: rgba(255,255,255,0);");
    ui->registrationbtn->setStyleSheet("background-color: rgba(255,255,255,0);");

    ui->nameline->setPlaceholderText("Имя");
    ui->passwordline->setPlaceholderText("Пароль");
    ui->passwordline2->setPlaceholderText("Пароль");
    ui->passwordline->setEchoMode(QLineEdit::Password);
    ui->passwordline2->setEchoMode(QLineEdit::Password);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_registrationbtn_clicked()
{
    if (ui->passwordline->text() == ui->passwordline2->text())
    {
        registration(ui->nameline->text(), ui->passwordline->text());
    }
}

void RegistrationForm::setError(QString error)
{
    ui->errorlbl->setText(error);
}
