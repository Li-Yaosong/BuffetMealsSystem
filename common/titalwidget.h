#ifndef TITALWIDGET_H
#define TITALWIDGET_H

#include <QWidget>
namespace Ui {
class TitalWidget;
}

class TitalWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TitalWidget(QWidget *parent = nullptr, QString tital = "", bool maxButton = true);
    ~TitalWidget();
protected:
    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

private slots:

    void on_pushButton_max_clicked();

    void on_pushButton_min_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::TitalWidget *ui;
    QWidget *m_parent;
    QPoint m_Difference;
    // QWidget interface

};

#endif // TITALWIDGET_H
