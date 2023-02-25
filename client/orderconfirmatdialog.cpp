#include "orderconfirmatdialog.h"
#include "ui_orderconfirmatdialog.h"

OrderConfirmatDialog::OrderConfirmatDialog(QMap<QString, int> map, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderConfirmatDialog)
{
    ui->setupUi(this);
    for(const QString &name : map.keys())
    {
        ui->textEdit->append(name
            + QString(" " + QString::number(map.value(name)) + QString::fromLocal8Bit("份")));
    }
}

OrderConfirmatDialog::~OrderConfirmatDialog()
{
    delete ui;
}
