#include "administratorinterface.h"
#include "orderlist.h"
#include "ui_administratorinterface.h"

AdministratorInterface::AdministratorInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdministratorInterface)
{
    ui->setupUi(this);
}

AdministratorInterface::~AdministratorInterface()
{
    delete ui;
}

void AdministratorInterface::on_noFinished_pushButton_clicked()
{
    OrderList *order = new OrderList();
    ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count() - 1,order);
}

