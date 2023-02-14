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
    QPixmap photo;
    photo.loadFromData(service->getData(), "JPG"); //从数据库中读出图片为二进制数据，图片格式为JPG，然后显示到QLabel里
    ui->label->setPixmap(photo);
    ui->label->setScaledContents(true);
//    m_clientApp->show();
//    connect(m_clientApp,SIGNAL(adminiLogin_clicked()),SLOT(showAdminiLogin()));
//    connect(m_clientApp,SIGNAL(customersLogin_clicked()),SLOT(showCustomersLogin()));
//    ui->tabWidget->removeTab(1);
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

