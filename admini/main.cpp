#include "admini.h"
#include "administratorinterface.h"
#include <QApplication>
#include "stylesheet.h"
#include "loginwidget.h"
#include "registwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(StyleSheet::style());
    AdministratorInterface w;
//    LogInWidget l;
//    RegistWidget r;
//    r.show();
//    l.show();
    w.show();
    return a.exec();
}
