#include "orderlist.h"
#include "ui_orderlist.h"
#include <QDebug>
#include "orderconfirmatdialog.h"
#include "connectservice.h"
OrderList::OrderList(Order order, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderList),
    m_num(order.num)
{
    ui->setupUi(this);
    ui->number_label->setText(QString::number(order.num));
    ui->seatNumber_label->setText(QString::number(order.seat));
    qDebug()<<order.time;
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(order.time, "yyyy-MM-ddThh:mm:ss.zzz"));
    ui->label_total->setText(QString::number(order.total));
    if(order.state)
    {
        ui->label_state->setText(QStringLiteral("已完成"));
    }
    else
    {
        ui->label_state->setText(QStringLiteral("未完成"));
    }
    QDataStream dishes(&order.dishes, QIODevice::OpenModeFlag::ReadOnly);
    dishes >> m_dishes;
}

OrderList::~OrderList()
{
    delete ui;
}

void OrderList::on_see_pushButton_clicked()
{
    OrderConfirmatDialog *dialog = new OrderConfirmatDialog(m_dishes);
    dialog->setButtonText(QStringLiteral("完成订单"),QStringLiteral("取消订单"));
    if(QDialog::Accepted == dialog->exec())
    {
        ConnectService::service()->rep()->updateOrder(m_num, 1);
        emit updateOrder();
    }
}

