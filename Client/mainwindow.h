#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QByteArray>
#include <QString>

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
public slots:
    void slotReadyRead();
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

private:
    void sendToServer(QString str);
    QTcpSocket* m_socket;
    QByteArray m_data;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
