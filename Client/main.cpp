#include "client.h"
#include <QApplication>
#include "message.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client;
    return a.exec();
}
