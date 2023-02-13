#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include "qobjectdefs.h"
#include <QWidget>
//#include "login.h"

namespace Ui {
class ClientApp;
}

class ClientApp : public QWidget
{
    Q_OBJECT

public:
    explicit ClientApp(QWidget *parent = nullptr);
    ~ClientApp();

signals:
    void adminiLogin_clicked();
    void customersLogin_clicked();

private:
    Ui::ClientApp *ui;
//    Login *m_logWidet;
};

#endif // CLIENTAPP_H
