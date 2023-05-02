#ifndef STYLESHEET_H
#define STYLESHEET_H

#include <QByteArray>
//#include "libbms_global.h"

class StyleSheet
{
public:
    static QByteArray style();
    static QByteArray buttonStyle(int style = 0);
    static QByteArray lineEditStyle();
    static QByteArray labelStyle(int style = 0);
    static QByteArray widgetStyle(int style = 0);
    static QByteArray comboBoxStyle();
    static QByteArray spinBoxStyle();
    static QByteArray scrollBarStyle();
};

#endif // STYLESHEET_H
