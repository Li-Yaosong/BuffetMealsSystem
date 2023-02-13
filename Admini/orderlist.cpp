#include "orderlist.h"
#include "ui_orderlist.h"

OrderList::OrderList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderList)
{
    ui->setupUi(this);
}

OrderList::~OrderList()
{
    delete ui;
}
