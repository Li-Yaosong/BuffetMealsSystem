#include "stylesheet.h"
#include <QFile>
QByteArray readQss(QString qss)
{
    QFile qssFile(qss);
    qssFile.open(QFile::ReadOnly);
    QByteArray style = qssFile.readAll();
    qssFile.close();
    return style;
}
QByteArray StyleSheet::style()
{
    return  readQss(":/StyleSheet.qss");
}

QByteArray StyleSheet::buttonStyle(int style)
{
    switch (style) {
    case 0:
        return  readQss(":/button.qss");
    case 1:
        return  readQss(":/button1.qss");
    case 2:
        return  readQss(":/button2.qss");
    case 3:
        return  readQss(":/qss/button3.qss");
    case 4:
        return  readQss(":/qss/button4.qss");
    default:
        return  readQss(":/button1.qss");
    }
}

QByteArray StyleSheet::lineEditStyle()
{
    return  readQss(":/lineedit.qss");
}

QByteArray StyleSheet::labelStyle(int style)
{
    switch (style) {
    case 0:
        return  readQss(":/lable.qss");
    case 1:
        return  readQss(":/label1.qss");
    case 2:
        return  readQss(":/qss/label2.qss");
    case 3:
        return  readQss(":/qss/label3.qss");
    default:
        return  readQss(":/lable.qss");
    }
}

QByteArray StyleSheet::widgetStyle(int style)
{
    switch (style) {
    case 0:
        return  readQss(":/qss/widget.qss");
    default:
        return  readQss(":/qss/widget.qss");
    }
}

QByteArray StyleSheet::comboBoxStyle()
{
    return  readQss(":/qss/combobox.qss");
}
