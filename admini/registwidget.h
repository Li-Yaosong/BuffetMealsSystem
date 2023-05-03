#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include <QWidget>

namespace Ui {
class RegistWidget;
}

class RegistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistWidget(QWidget *parent = nullptr);
    ~RegistWidget();

    void initStyle();
signals:
    void backLogin();
private slots:
    void on_pushButton_regist_clicked();
    void textChanged_slot();

private:
    Ui::RegistWidget *ui;
};

#endif // REGISTWIDGET_H
