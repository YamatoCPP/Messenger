#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addMessage(QString str);

signals:
    void sendToServer(QString str);
private slots:
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
