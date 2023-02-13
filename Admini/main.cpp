#include "admini.h"
#include "administratorinterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdministratorInterface w;
    w.show();
    return a.exec();
}
