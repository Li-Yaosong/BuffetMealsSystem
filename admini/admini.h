#ifndef ADMINI_H
#define ADMINI_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Admini; }
QT_END_NAMESPACE

class Admini : public QWidget
{
    Q_OBJECT

public:
    Admini(QWidget *parent = nullptr);
    ~Admini();

private:
    Ui::Admini *ui;
};
#endif // ADMINI_H
