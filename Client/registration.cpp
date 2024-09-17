#include "registration.h"
#include "ui_registration.h"

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
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
