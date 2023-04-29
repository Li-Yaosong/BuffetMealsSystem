/* ************************************************************************************************
 * class Name :
 *
 * describe:
 *
 * function:
 *
 * Create Time : 2023-02-28 14:24:30
 * By liyaosong
 **************************************************************************************************/
#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>

namespace Ui {
class Console;
}

class Console : public QWidget
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);
    ~Console();
    void appendDebug(QString info);

private:
    Ui::Console *ui;
};

#endif // CONSOLE_H
