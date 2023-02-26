#include "admini.h"
#include "administratorinterface.h"
#include <QApplication>
#include "stylesheet.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(StyleSheet::style());
    AdministratorInterface w;
    w.show();
    return a.exec();
}
