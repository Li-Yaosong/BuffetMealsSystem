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
//    qDebug()<<order.time;
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(order.time, "yyyy-MM-ddThh:mm:ss.zzz"));
    ui->label_total->setText(QString::number(order.total));
    m_total = order.total;
    m_state = order.state;
    m_date = QDateTime::fromString(order.time,"yyyy-MM-ddThh:mm:ss.zzz").toString("yyyy-MM-dd");
    qDebug()<<m_date;
    if(m_state == 0)
    {
        ui->label_state->setText(QStringLiteral("未完成"));
    }
    else if(m_state == 1)
    {
        ui->label_state->setText(QStringLiteral("已完成"));
    }
    else
    {
        ui->label_state->setText(QStringLiteral("已结算"));
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
    dialog->setState(m_state);
    if(QDialog::Accepted == dialog->exec())
    {
        if(dialog->state() == 0)
        {
            dialog->setState(1);
            ConnectService::service()->rep()->updateOrder(m_num, 1);
        }
        else if(dialog->state() == 1)
        {
            dialog->setState(2);
            ConnectService::service()->rep()->updateOrder(m_num, 2);

            ConnectService::service()->rep()->updateReport(m_date, m_total);
        }
        emit updateOrder();
    }
}

