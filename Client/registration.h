#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

    void setError(QString error);
private slots:
    void on_registrationbtn_clicked();

signals:
    void registration(QString name, QString password);

private:

    Ui::RegistrationForm *ui;
};

#endif // REGISTRATION_H
