#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LogInWidget;
}
class AdministratorInterface;
class LogInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LogInWidget(QWidget *parent = nullptr);
    ~LogInWidget();

    void initStyle();

private slots:
    void on_pushButton_login_clicked();
    void textChanged_slot();

    void on_pushButton_regist_clicked();

private:
    Ui::LogInWidget *ui;
    AdministratorInterface *m_interface;
};

#endif // LOGINWIDGET_H
