#ifndef REPORTWIDGET_H
#define REPORTWIDGET_H

#include <QWidget>
#include "global.h"
namespace Ui {
class ReportWidget;
}
class ReportWidgetPrivate;
class ReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReportWidget(QWidget *parent = nullptr);
    ~ReportWidget();
    void addRowReport();
    void initReport(QList<Report> list);

private:
    Ui::ReportWidget *ui;
    ReportWidgetPrivate * const p;
};

#endif // REPORTWIDGET_H
