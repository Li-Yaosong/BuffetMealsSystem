#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "clientapp.h"
#include "administratorinterface.h"
#include <QObject>
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void setIdentity(bool identity);

private slots:
    void showAdminiLogin();
    void showCustomersLogin();


    void on_AdminiLogin_pushButton_clicked();

private:
    Ui::Login *ui;
    bool m_identity;
    ClientApp * m_clientApp;
    AdministratorInterface *m_AdInterface;
};

#endif // LOGIN_H
