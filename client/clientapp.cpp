#include "clientapp.h"
#include "ui_clientapp.h"

ClientApp::ClientApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientApp)
{
    ui->setupUi(this);
//    m_logWidet = new Login();
    connect(ui->adminiLogin,SIGNAL(clicked()),this,SIGNAL(adminiLogin_clicked()));
    connect(ui->customersLogin,SIGNAL(clicked()),this,SIGNAL(customersLogin_clicked()));
}

ClientApp::~ClientApp()
{
    delete ui;
}
