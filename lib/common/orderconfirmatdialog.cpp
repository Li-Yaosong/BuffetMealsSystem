#include "orderconfirmatdialog.h"
#include "ui_orderconfirmatdialog.h"
#include "titalwidget.h"
#include <QPushButton>
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
    TitalWidget *tital = new TitalWidget(this, QStringLiteral("订单信息"), false);
    ui->verticalLayout->insertWidget(0, tital);
    setButtonText();
}

OrderConfirmatDialog::~OrderConfirmatDialog()
{
    delete ui;
}

void OrderConfirmatDialog::setButtonText(QString ok, QString cancel)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(ok);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(cancel);
}
