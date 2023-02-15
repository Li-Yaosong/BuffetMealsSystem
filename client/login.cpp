#include "login.h"
#include "ui_login.h"
#include <QPixmap>
#include "connectservice.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{

    ui->setupUi(this);
    this->hide();
    m_clientApp = new ClientApp;
    ConnectService *service = new ConnectService;
}

Login::~Login()
{
    delete ui;
}

void Login::setIdentity(bool identity)
{
    m_identity = identity;
    if(identity)
    {
        ui->tabWidget->removeTab(1);
    }
    else
    {
        ui->tabWidget->removeTab(0);
    }

}

void Login::showAdminiLogin()
{
    ui->tabWidget->removeTab(0);
    this->show();
    m_clientApp->hide();
}

void Login::showCustomersLogin()
{
    ui->tabWidget->removeTab(1);
    this->show();
    m_clientApp->hide();
}

void Login::on_AdminiLogin_pushButton_clicked()
{
}

