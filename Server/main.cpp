#include <QCoreApplication>
#include "server.h"
#include "databasemanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    DataBaseManager db;
    return a.exec();
}
