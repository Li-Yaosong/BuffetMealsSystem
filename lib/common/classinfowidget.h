#ifndef CLASSINFOWIDGET_H
#define CLASSINFOWIDGET_H
//#include "libbms_global.h"
#include <QWidget>
#include <QMap>

#include "global.h"
namespace Ui {
class ClassInfoWidget;
}

class ClassInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClassInfoWidget(QWidget *parent = nullptr);
    ~ClassInfoWidget();
    Class info();
signals:
    void infoChanged(Class);

private slots:
    void on_pushButton_browse_clicked();
    void textChanged();

private:
    void initStyle();
    Ui::ClassInfoWidget *ui;
    Class m_info;
};

#endif // CLASSINFOWIDGET_H
