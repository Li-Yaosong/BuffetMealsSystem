//#include "clientapp.h"
//#include "login.h"
#include "clientinterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ClientApp w;
    ClientInterface w;
    w.show();

    return a.exec();
}
